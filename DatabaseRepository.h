#pragma once
#include "Repository.h"
#include "SimpleEvidenceValidator.h"
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

class DatabaseRepository : public Repository
{
private:
	SQLHANDLE _environment_handle, _connection_handle;
	const EvidenceValidator& _validator;
	void _throw_database_error(unsigned int handle_type, const SQLHANDLE& handle) const;
	SQLHANDLE _run_statement(std::string statement) const;
	void _sort_data() const;
	std::string _escape_string(const std::string& string) const;

public:
	DatabaseRepository(std::string connection_string,
	                   const EvidenceValidator& Validator = *new SimpleEvidenceValidator());

	int Size() const override;

	void AddEvidence(const Evidence& evidence) override;

	Evidence RemoveEvidence(std::string evidence_id) override;

	Evidence UpdateEvidence(const Evidence& evidence) override;

	Evidence AtIndex(int index) const override;

	Evidence AtID(std::string evidence_id) const override;

	void OpenFile() const override;

	~DatabaseRepository();
};
