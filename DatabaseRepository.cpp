#include "DatabaseRepository.h"
#include <sstream>
#include "SetDebugNew.h"

using namespace std;

void DatabaseRepository::_throw_database_error(unsigned int handle_type, const SQLHANDLE& handle) const
{
	ostringstream result;
	SQLCHAR sqlstate[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRecA(handle_type, handle, 1, sqlstate, nullptr, message, 1024, nullptr))
		result << "Message: " << message << "\nSQLSTATE: " << sqlstate << endl;
	throw RepositoryException(result.str());
}

SQLHANDLE DatabaseRepository::_run_statement(string statement) const
{
	SQLHANDLE statement_handle;
	if (SQLAllocHandle(SQL_HANDLE_STMT, _connection_handle, &statement_handle) != SQL_SUCCESS)
		throw RepositoryException("Could not run SQL statement: " + statement);
	if (SQLExecDirectA(statement_handle, (SQLCHAR*)statement.c_str(), SQL_NTS) == SQL_ERROR)
		_throw_database_error(SQL_HANDLE_STMT, statement_handle);
	return statement_handle;
}

void DatabaseRepository::_sort_data() const
{
	SQLFreeHandle(SQL_HANDLE_STMT,
	              _run_statement(
		              "update Evidence set OrderedID = x.New_OrderedID - 1 from ( select EvidenceID, ROW_NUMBER() over (order by EvidenceID) as New_OrderedID from Evidence) x where Evidence.[EvidenceID] = x.EvidenceID"));
}

std::string DatabaseRepository::_escape_string(const std::string& string) const
{
	if (string == "")
		return "";
	istringstream in(string);
	ostringstream out;
	std::string chunk;
	while (getline(in, chunk, '\''))
		out << chunk << "''";
	return *(string.end() - 1) == '\'' ? out.str() : out.str().substr(0, out.str().size() - 2);
}

DatabaseRepository::DatabaseRepository(std::string connection_string, const EvidenceValidator& Validator) : _validator(
	Validator)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &_environment_handle))
		throw RepositoryException("Could not allocate environment handle.");
	if (SQL_SUCCESS != SQLSetEnvAttr(_environment_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		throw RepositoryException("Could not set ODBC version to 3.");
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, _environment_handle, &_connection_handle))
		throw RepositoryException("Could not allocate connection handle");
	SQLCHAR returned_connection_string[1024];
	if (SQLDriverConnectA(_connection_handle, nullptr, (SQLCHAR*)connection_string.c_str(), SQL_NTS,
	                      returned_connection_string, 1024, nullptr, SQL_DRIVER_NOPROMPT) == SQL_ERROR)
		_throw_database_error(SQL_HANDLE_DBC, _connection_handle);
}

int DatabaseRepository::Size() const
{
	SQLHANDLE handle = _run_statement("select COUNT(*) from evidence");
	int result;
	if (SQLFetch(handle) != SQL_SUCCESS)
		throw RepositoryException("Could not get number of elements in database.");
	SQLGetData(handle, 1, SQL_C_DEFAULT, &result, 0, nullptr);
	SQLFreeHandle(SQL_HANDLE_STMT, handle);
	return result;
}

void DatabaseRepository::AddEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	SQLHANDLE check_ID_handle = _run_statement("select TOP 1 NumericID from Evidence where EvidenceID = '" +
		_escape_string(evidence.ID()) + "'");
	if (SQLFetch(check_ID_handle) == SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);
		throw RepositoryException("Duplicate ID.");
	}
	SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);

	SQLHANDLE add_row_handle =
		_run_statement("insert into Evidence values (0, '" +
			_escape_string(evidence.ID()) + "', " +
			to_string(evidence.MeasurementX()) + ", " +
			to_string(evidence.MeasurementY()) + ", " +
			to_string(evidence.MeasurementZ()) + ", " +
			to_string(evidence.ImageClarityLevel()) + ", " +
			to_string(evidence.Quantity()) + ", '" +
			_escape_string(evidence.Photograph()) + "')"
		);
	SQLFreeHandle(SQL_HANDLE_STMT, add_row_handle);

	_sort_data();
}

Evidence DatabaseRepository::RemoveEvidence(std::string evidence_id)
{
	SQLHANDLE check_ID_handle = _run_statement("select TOP 1 * from Evidence where EvidenceID = '" +
		_escape_string(evidence_id) + "'");
	if (SQLFetch(check_ID_handle) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);
		throw RepositoryException("ID does not exist.");
	}

	int to_remove_key;
	char db_evidence_id[SQL_MAX_MESSAGE_LENGTH], photograph[SQL_MAX_MESSAGE_LENGTH];
	unsigned int measurements[3], quantity;
	float image_clarity;
	SQLGetData(check_ID_handle, 1, SQL_C_DEFAULT, &to_remove_key, 0, nullptr);
	SQLGetData(check_ID_handle, 3, SQL_C_DEFAULT, db_evidence_id, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLGetData(check_ID_handle, 4, SQL_C_DEFAULT, measurements, 0, nullptr);
	SQLGetData(check_ID_handle, 5, SQL_C_DEFAULT, measurements + 1, 0, nullptr);
	SQLGetData(check_ID_handle, 6, SQL_C_DEFAULT, measurements + 2, 0, nullptr);
	SQLGetData(check_ID_handle, 7, SQL_C_FLOAT, &image_clarity, 0, nullptr);
	SQLGetData(check_ID_handle, 8, SQL_C_DEFAULT, &quantity, 0, nullptr);
	SQLGetData(check_ID_handle, 9, SQL_C_DEFAULT, photograph, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);

	SQLHANDLE remove_row_handle = _run_statement("delete from Evidence where NumericID = " + to_string(to_remove_key));
	SQLFreeHandle(SQL_HANDLE_STMT, remove_row_handle);

	_sort_data();

	return Evidence(string(db_evidence_id), measurements, image_clarity, quantity, string(photograph));
}

Evidence DatabaseRepository::UpdateEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	SQLHANDLE check_ID_handle = _run_statement("select TOP 1 * from Evidence where EvidenceID = '" +
		_escape_string(evidence.ID()) + "'");
	if (SQLFetch(check_ID_handle) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);
		throw RepositoryException("ID does not exist.");
	}

	int to_update_key;
	char db_evidence_id[SQL_MAX_MESSAGE_LENGTH], photograph[SQL_MAX_MESSAGE_LENGTH];
	unsigned int measurements[3], quantity;
	float image_clarity;
	SQLGetData(check_ID_handle, 1, SQL_C_DEFAULT, &to_update_key, 0, nullptr);
	SQLGetData(check_ID_handle, 3, SQL_C_DEFAULT, db_evidence_id, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLGetData(check_ID_handle, 4, SQL_C_DEFAULT, measurements, 0, nullptr);
	SQLGetData(check_ID_handle, 5, SQL_C_DEFAULT, measurements + 1, 0, nullptr);
	SQLGetData(check_ID_handle, 6, SQL_C_DEFAULT, measurements + 2, 0, nullptr);
	SQLGetData(check_ID_handle, 7, SQL_C_FLOAT, &image_clarity, 0, nullptr);
	SQLGetData(check_ID_handle, 8, SQL_C_DEFAULT, &quantity, 0, nullptr);
	SQLGetData(check_ID_handle, 9, SQL_C_DEFAULT, photograph, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLFreeHandle(SQL_HANDLE_STMT, check_ID_handle);

	SQLHANDLE update_row_handle =
		_run_statement("update Evidence set "
			"MeasurementX = " + to_string(evidence.MeasurementX()) + ", " +
			"MeasurementY = " + to_string(evidence.MeasurementY()) + ", " +
			"MeasurementZ = " + to_string(evidence.MeasurementZ()) + ", " +
			"ImageClarityLevel = " + to_string(evidence.ImageClarityLevel()) + ", " +
			"Quantity = " + to_string(evidence.Quantity()) + ", " +
			"Photograph = '" + _escape_string(evidence.Photograph()) + "' where NumericID = " +
			to_string(to_update_key));
	SQLFreeHandle(SQL_HANDLE_STMT, update_row_handle);
	return Evidence(string(db_evidence_id), measurements, image_clarity, quantity, string(photograph));
}

Evidence DatabaseRepository::AtIndex(int index) const
{
	if (index < 0 || index >= Size())
		throw RepositoryException("Index out of bounds.");
	SQLHANDLE find_row_handle =
		_run_statement("select TOP 1 * from Evidence where OrderedID = " + to_string(index));
	if (SQLFetch(find_row_handle) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, find_row_handle);
		throw RepositoryException("SQL Server error.");
	}
	char db_evidence_id[SQL_MAX_MESSAGE_LENGTH], photograph[SQL_MAX_MESSAGE_LENGTH];
	unsigned int measurements[3], quantity;
	float image_clarity;
	SQLGetData(find_row_handle, 3, SQL_C_DEFAULT, db_evidence_id, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLGetData(find_row_handle, 4, SQL_C_DEFAULT, measurements, 0, nullptr);
	SQLGetData(find_row_handle, 5, SQL_C_DEFAULT, measurements + 1, 0, nullptr);
	SQLGetData(find_row_handle, 6, SQL_C_DEFAULT, measurements + 2, 0, nullptr);
	SQLGetData(find_row_handle, 7, SQL_C_FLOAT, &image_clarity, 0, nullptr);
	SQLGetData(find_row_handle, 8, SQL_C_DEFAULT, &quantity, 0, nullptr);
	SQLGetData(find_row_handle, 9, SQL_C_DEFAULT, photograph, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLFreeHandle(SQL_HANDLE_STMT, find_row_handle);
	return Evidence(string(db_evidence_id), measurements, image_clarity, quantity, string(photograph));
}

Evidence DatabaseRepository::AtID(std::string evidence_id) const
{
	SQLHANDLE find_row_handle =
		_run_statement("select TOP 1 * from Evidence where EvidenceID = '" + _escape_string(evidence_id) + "'");
	if (SQLFetch(find_row_handle) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, find_row_handle);
		throw RepositoryException("ID does not exist.");
	}
	char db_evidence_id[SQL_MAX_MESSAGE_LENGTH], photograph[SQL_MAX_MESSAGE_LENGTH];
	unsigned int measurements[3], quantity;
	float image_clarity;
	SQLGetData(find_row_handle, 3, SQL_C_DEFAULT, db_evidence_id, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLGetData(find_row_handle, 4, SQL_C_DEFAULT, measurements, 0, nullptr);
	SQLGetData(find_row_handle, 5, SQL_C_DEFAULT, measurements + 1, 0, nullptr);
	SQLGetData(find_row_handle, 6, SQL_C_DEFAULT, measurements + 2, 0, nullptr);
	SQLGetData(find_row_handle, 7, SQL_C_FLOAT, &image_clarity, 0, nullptr);
	SQLGetData(find_row_handle, 8, SQL_C_DEFAULT, &quantity, 0, nullptr);
	SQLGetData(find_row_handle, 9, SQL_C_DEFAULT, photograph, SQL_MAX_MESSAGE_LENGTH, nullptr);
	SQLFreeHandle(SQL_HANDLE_STMT, find_row_handle);
	return Evidence(string(db_evidence_id), measurements, image_clarity, quantity, string(photograph));
}

void DatabaseRepository::OpenFile() const
{
	throw RepositoryException("Current repository is connected to a database.");
}

DatabaseRepository::~DatabaseRepository()
{
	SQLDisconnect(_connection_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, _connection_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, _environment_handle);
	delete&_validator;
}
