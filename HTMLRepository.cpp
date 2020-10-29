#define _CRT_SECURE_NO_WARNINGS
#include "HTMLRepository.h"
#include "HTMLIO.h"
#include <fstream>
#include <sstream>
#include "SetDebugNew.h"
using namespace std;

void HTMLRepository::_write_file_begin(ostream& out)
{
	out << TagOut("!DOCTYPE") << TagAttributes("html") << '\n'
		<< TagOut("html") << '\n'
		<< TagOut("head") << '\n'
		<< TagOut("title")
		<< "Evidence"
		<< TagOut("/title") << '\n'
		<< TagOut("/head") << '\n'
		<< TagOut("body") << '\n'
		<< TagOut("table") << TagAttributes("border=\"1\"") << '\n'
		<< TagOut("tr") << '\n'
		<< TagOut("td") << '\n'
		<< "ID\n"
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< "Measurement\n"
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< "Image clarity level\n"
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< "Quantity\n"
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< "Photograph\n"
		<< TagOut("/td") << '\n'
		<< TagOut("/tr") << '\n';
}

void HTMLRepository::_write_file_end(ostream& out)
{
	out << TagOut("/table") << '\n'
		<< TagOut("/body") << '\n'
		<< TagOut("/html") << '\n';
}

Evidence HTMLRepository::_move_evidence_until_ID(std::istream& in, std::ostream& out, std::string ID,
                                                 istringstream& table_data)
{
	TagIn current_tag;
	while (in >> current_tag && current_tag.GetName() != "html");
	if (current_tag.GetName() == "html")
	{
		do
		{
			istringstream content(current_tag.GetContent());
			content >> current_tag;
			if (current_tag.GetName() == "head")
				content >> current_tag;
		}
		while (current_tag.GetName() != "table");
		TagIn RecordTag, IDTag, MeasurementTag, ClarityTag, QuantityTag, PhotoTag;
		Evidence* current_record;
		table_data = istringstream(current_tag.GetContent());
		table_data >> RecordTag;
		while (table_data >> RecordTag)
		{
			istringstream evidence_data(RecordTag.GetContent());
			evidence_data >> IDTag >> MeasurementTag >> ClarityTag >> QuantityTag >> PhotoTag;
			current_record = Evidence::FromString(
				IDTag.GetContent() + "," + MeasurementTag.GetContent() + "," + ClarityTag.GetContent() + "," +
				QuantityTag.GetContent() + "," + PhotoTag.GetContent());
			if (current_record->ID() >= ID)
			{
				Evidence to_return = *current_record;
				delete current_record;
				return to_return;
			}
			out << _evidence_to_html(*current_record) << '\n';
			delete current_record;
		}
	}
	return Evidence();
}

void HTMLRepository::_copy_data(std::istream& table_data, std::ostream& out)
{
	char buffer[1001];
	while (table_data.read(buffer, 1000)) out.write(buffer, 1000);
	if (table_data.gcount() > 0)
		out.write(buffer, table_data.gcount());
}

std::string HTMLRepository::_evidence_to_html(const Evidence& Evidence)
{
	ostringstream result;
	result << TagOut("tr") << '\n'
		<< TagOut("td") << '\n'
		<< Evidence.ID() << '\n'
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< Evidence.MeasurementString() << '\n'
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< Evidence.ImageClarityLevel() << '\n'
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< Evidence.Quantity() << '\n'
		<< TagOut("/td") << '\n'
		<< TagOut("td") << '\n'
		<< Evidence.Photograph() << '\n'
		<< TagOut("/td") << '\n'
		<< TagOut("/tr") << "";
	return result.str();
}

HTMLRepository::HTMLRepository(std::string file, const EvidenceValidator& Validator) : _validator(Validator)
{
	SetFile(file);
}

int HTMLRepository::Size() const
{
	if (_file == "") throw RepositoryException("No file set.");
	return _size;
}

void HTMLRepository::AddEvidence(const Evidence& evidence)
{
	if (_file == "") throw RepositoryException("No file set.");
	_validator.Validate(evidence);
	int item_count = Size();
	if (item_count == 0)
	{
		ofstream out(_file);
		_write_file_begin(out);
		out << _evidence_to_html(evidence) << endl;
		_write_file_end(out);
		++_size;
		return;
	}
	string temporary_file = tmpnam(nullptr);
	const string& evidence_id = evidence.ID();
	ifstream in(_file);
	ofstream out(temporary_file);
	_write_file_begin(out);
	istringstream table_data;
	Evidence found = _move_evidence_until_ID(in, out, evidence_id, table_data);
	if (found.ID() == "")
	{
		out << _evidence_to_html(evidence) << endl;
		_copy_data(table_data, out);
		_write_file_end(out);
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
	out << _evidence_to_html(evidence) << endl << _evidence_to_html(found) << endl;
	_copy_data(table_data, out);
	_write_file_end(out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	++_size;
}

Evidence HTMLRepository::RemoveEvidence(std::string evidence_id)
{
	if (Size() == 0)
		throw RepositoryException("No evidence to remove");
	string temporary_file = tmpnam(nullptr);
	ifstream in(_file);
	ofstream out(temporary_file);
	istringstream table_data;
	_write_file_begin(out);
	Evidence found = _move_evidence_until_ID(in, out, evidence_id, table_data);
	if (found.ID() != evidence_id)
	{
		in.close();
		out.close();
		remove(temporary_file.c_str());
		throw RepositoryException("ID not found");
	}
	_copy_data(table_data, out);
	_write_file_end(out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	--_size;
	return found;
}

Evidence HTMLRepository::UpdateEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	if (Size() == 0)
		throw RepositoryException("No evidence to remove");
	string temporary_file = tmpnam(nullptr);
	ifstream in(_file);
	ofstream out(temporary_file);
	string evidence_id = evidence.ID();
	istringstream table_data;
	_write_file_begin(out);
	Evidence found = _move_evidence_until_ID(in, out, evidence_id, table_data);
	if (found.ID() != evidence_id)
	{
		in.close();
		out.close();
		remove(temporary_file.c_str());
		throw RepositoryException("ID not found");
	}
	out << _evidence_to_html(evidence) << endl;
	_copy_data(table_data, out);
	_write_file_end(out);
	in.close();
	out.close();
	remove(_file.c_str());
	rename(temporary_file.c_str(), _file.c_str());
	return found;
}

Evidence HTMLRepository::AtIndex(int index) const
{
	if (index > Size() || index < 0)
		throw RepositoryException("Index out of bounds");
	ifstream in(_file);
	TagIn current_tag;
	while (in >> current_tag && current_tag.GetName() != "html");
	if (current_tag.GetName() == "html")
	{
		do
		{
			istringstream content(current_tag.GetContent());
			content >> current_tag;
			if (current_tag.GetName() == "head")
				content >> current_tag;
		}
		while (current_tag.GetName() != "table");
		TagIn RecordTag, IDTag, MeasurementTag, ClarityTag, QuantityTag, PhotoTag;
		Evidence* current_record;
		istringstream table_data = istringstream(current_tag.GetContent());
		table_data >> RecordTag;
		while (index-- > -1 && table_data >> RecordTag);
		istringstream evidence_data(RecordTag.GetContent());
		evidence_data >> IDTag >> MeasurementTag >> ClarityTag >> QuantityTag >> PhotoTag;
		current_record = Evidence::FromString(
			IDTag.GetContent() + "," + MeasurementTag.GetContent() + "," + ClarityTag.GetContent() + "," + QuantityTag.
			GetContent() + "," + PhotoTag.GetContent());
		Evidence to_return = *current_record;
		delete current_record;
		return to_return;
	}
	throw RepositoryException("Invalid html.");
}

Evidence HTMLRepository::AtID(std::string evidence_id) const
{
	ifstream in(_file);
	TagIn current_tag;
	while (in >> current_tag && current_tag.GetName() != "html");
	if (current_tag.GetName() == "html")
	{
		do
		{
			istringstream content(current_tag.GetContent());
			content >> current_tag;
			if (current_tag.GetName() == "head")
				content >> current_tag;
		}
		while (current_tag.GetName() != "table");
		TagIn RecordTag, IDTag, MeasurementTag, ClarityTag, QuantityTag, PhotoTag;
		Evidence* current_record;
		istringstream table_data(current_tag.GetContent());
		table_data >> RecordTag;
		while (table_data >> RecordTag)
		{
			istringstream evidence_data(RecordTag.GetContent());
			evidence_data >> IDTag >> MeasurementTag >> ClarityTag >> QuantityTag >> PhotoTag;
			current_record = Evidence::FromString(
				IDTag.GetContent() + "," + MeasurementTag.GetContent() + "," + ClarityTag.GetContent() + "," +
				QuantityTag.GetContent() + "," + PhotoTag.GetContent());
			if (current_record->ID() >= evidence_id)
			{
				if (current_record->ID() == evidence_id)
				{
					Evidence to_return = *current_record;
					delete current_record;
					return to_return;
				}
				throw RepositoryException("ID not found.");
			}
			delete current_record;
		}
		return Evidence();
	}
	throw RepositoryException("Invalid html.");
}

void HTMLRepository::SetFile(std::string file)
{
	if (FILE* descriptor = fopen(file.c_str(), "r")) // check if file exists
		fclose(descriptor);
	else
		fclose(fopen(file.c_str(), "w")); // create it
	_file = file;
	TagIn dummy;
	_size = 0;
	ifstream in(_file);
	while (in >> dummy && dummy.GetName() != "html");
	if (dummy.GetName() == "html")
	{
		do
		{
			istringstream content(dummy.GetContent());
			content >> dummy;
			if (dummy.GetName() == "head")
				content >> dummy;
		}
		while (dummy.GetName() != "table");
		istringstream records(dummy.GetContent());
		records >> dummy;
		while (records >> dummy)
			++_size;
	}
}

void HTMLRepository::OpenFile() const
{
	if (_file == "")
		throw RepositoryException("No file set.");
	system(_file.c_str());
}

HTMLRepository::~HTMLRepository()
{
	delete&_validator;
}
