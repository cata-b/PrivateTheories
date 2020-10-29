#define _CRT_SECURE_NO_WARNINGS

#include "FileRepository.h"
#include <exception>
#include <string>

#include "SetDebugNew.h"
using namespace std;

Evidence FileRepository::_move_evidence_until_ID(ifstream& original, ofstream& temp, std::string ID)
{
	Evidence file_line;
	while (original >> file_line)
	{
		if (file_line.ID() >= ID)
			return file_line;
		temp << file_line << endl;
	}
	return Evidence();
}

void FileRepository::_copy_file(std::ifstream& in, std::ofstream& out)
{
	char buffer[1001];
	while (in.read(buffer, 1000)) out.write(buffer, 1000);
	if (in.gcount() > 0)
		out.write(buffer, in.gcount());
}

FileRepository::FileRepository(string file, const EvidenceValidator& Validator) : _size(0), _file(file),
                                                                                  _validator(Validator)
{
	SetFile(file);
}

int FileRepository::Size() const
{
	if (_file == "") throw RepositoryException("No file set.");
	return _size;
}

void FileRepository::AddEvidence(const Evidence& evidence)
{
	if (_file == "") throw RepositoryException("No file set.");
	_validator.Validate(evidence);
	int item_count = Size();
	if (item_count == 0)
	{
		ofstream out;
		out.open(_file, ofstream::app);
		out << evidence << endl;
		++_size;
		return;
	}
	string temporary_file = tmpnam(nullptr);
	const string& evidence_id = evidence.ID();
	ifstream in(_file);
	ofstream out(temporary_file);
	Evidence found = _move_evidence_until_ID(in, out, evidence_id);
	if (found.ID() == "")
	{
		out << evidence << endl;
		_copy_file(in, out);
		in.close();
		out.close();
		remove(_file.c_str());
		rename(temporary_file.c_str(), _file.c_str());
		++_size;
		return;
	}
	if (found.ID() == evidence_id)
	{
		in.close();
		out.close();
		remove(temporary_file.c_str());
		throw RepositoryException("Duplicate ID");
	}
	out << evidence << endl << found << endl;
	_copy_file(in, out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	++_size;
}

Evidence FileRepository::RemoveEvidence(std::string evidence_id)
{
	if (Size() == 0)
		throw RepositoryException("No evidence to remove");
	string temporary_file = tmpnam(nullptr);
	ifstream in(_file);
	ofstream out(temporary_file);
	Evidence found = _move_evidence_until_ID(in, out, evidence_id);
	if (found.ID() != evidence_id)
	{
		in.close();
		out.close();
		remove(temporary_file.c_str());
		throw RepositoryException("ID not found");
	}
	_copy_file(in, out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	--_size;
	return found;
}

Evidence FileRepository::UpdateEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	if (Size() == 0)
		throw RepositoryException("No evidence to remove");
	string temporary_file = tmpnam(nullptr);
	ifstream in(_file);
	ofstream out(temporary_file);
	string evidence_id = evidence.ID();
	Evidence found = _move_evidence_until_ID(in, out, evidence_id);
	if (found.ID() != evidence_id)
	{
		in.close();
		out.close();
		remove(temporary_file.c_str());
		throw RepositoryException("ID not found");
	}
	out << evidence << endl;
	_copy_file(in, out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	return found;
}

Evidence FileRepository::AtIndex(int index) const
{
	if (index >= Size() || index < 0)
		throw RepositoryException("Index out of bounds");
	ifstream in(_file);
	Evidence dummy;
	while (index-- > -1)
		in >> dummy;
	return dummy;
}

Evidence FileRepository::AtID(std::string evidence_id) const
{
	ifstream in(_file);
	Evidence dummy;
	while (in >> dummy && dummy.ID() != evidence_id);
	if (dummy.ID() == evidence_id) return dummy;
	throw RepositoryException("ID not found.");
}

void FileRepository::SetFile(std::string file)
{
	if (FILE* descriptor = fopen(file.c_str(), "r")) // check if file exists
		fclose(descriptor);
	else
		fclose(fopen(file.c_str(), "w")); // create it
	_file = file;
	Evidence dummy;
	_size = 0;
	ifstream in(_file);
	while (in >> dummy) _size++;
}

void FileRepository::OpenFile() const
{
	if (_file == "")
		throw RepositoryException("No file set.");
	system(_file.c_str());
}

FileRepository::~FileRepository() { delete&_validator; }
