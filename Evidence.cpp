#include "Evidence.h"
#include "SimpleEvidenceValidator.h"
#include <sstream>
#include <algorithm>
#include "SetDebugNew.h"
using namespace std;

Evidence::Evidence() :
	_id(""),
	_photograph(""),
	_image_clarity_level(0),
	_quantity(0),
	_measurement{0, 0, 0}
{
}

Evidence::Evidence(const Evidence& EvidenceToCopy) :
	_id(EvidenceToCopy._id),
	_photograph(EvidenceToCopy._photograph),
	_image_clarity_level(EvidenceToCopy._image_clarity_level),
	_quantity(EvidenceToCopy._quantity)
{
	copy(EvidenceToCopy._measurement, EvidenceToCopy._measurement + 3, _measurement);
}

Evidence::Evidence(const string& ID, unsigned int Measurement[3], float ImageClarityLevel, unsigned int Quantity,
                   const string& Photograph) :
	_id(ID),
	_photograph(Photograph),
	_image_clarity_level(ImageClarityLevel),
	_quantity(Quantity)
{
	copy(Measurement, Measurement + 3, _measurement);
}

bool Evidence::IsValid() const
{
	return
		_image_clarity_level >= 0 &&
		_measurement[0] > 0 && _measurement[1] >= 0 && _measurement[2] >= 0 &&
		_quantity >= 1;
}

const string& Evidence::ID() const { return _id; }

string Evidence::MeasurementString() const
{
	return to_string(_measurement[0]) + "X" + to_string(_measurement[1]) + "X" + to_string(_measurement[2]);
}

int Evidence::MeasurementX() const { return _measurement[0]; }

int Evidence::MeasurementY() const { return _measurement[1]; }

int Evidence::MeasurementZ() const { return _measurement[2]; }

float Evidence::ImageClarityLevel() const { return _image_clarity_level; }

unsigned int Evidence::Quantity() const { return _quantity; }

const string& Evidence::Photograph() const { return _photograph; }

void* Evidence::CopyEvidence(void* evidence) { return new Evidence(*static_cast<Evidence*>(evidence)); }

void Evidence::DestroyEvidence(void* evidence) { delete static_cast<Evidence*>(evidence); }

Evidence* Evidence::FromString(const std::string& String)
{
	istringstream splitter(String);
	Evidence evidence;
	if (splitter >> evidence)
		return new Evidence(evidence);
	return new Evidence();
}

std::string to_string(const Evidence& evidence)
{
	string clarity_level_string = to_string(evidence.ImageClarityLevel());
	clarity_level_string = clarity_level_string.substr(0, clarity_level_string.find_last_not_of('0') + 1);
	if (clarity_level_string.back() == '.') clarity_level_string = clarity_level_string.substr(
		0, clarity_level_string.size() - 1);
	return
		evidence.ID() + "," +
		evidence.MeasurementString() + "," +
		clarity_level_string + "," +
		to_string(evidence.Quantity()) + "," +
		evidence.Photograph();
}

istream& operator>>(istream& in, Evidence& evidence)
{
	string line;
	getline(in, line);
	if (line[0] == ' ')
		line.erase(line.begin());
	istringstream splitter(line);
	string id, photograph, measurement_string, clarity_level_string, quantity_string;
	unsigned int measurement[3]{0, 0, 0};
	getline(splitter, id, ',');
	getline(splitter, measurement_string, ',');
	getline(splitter, clarity_level_string, ',');
	getline(splitter, quantity_string, ',');
	getline(splitter, photograph, ',');
	if (photograph[0] == ' ')
		photograph.erase(photograph.begin());
	istringstream measurement_splitter(measurement_string);
	int current_measurement_count = 0;
	string current_measurement;
	while (getline(measurement_splitter, current_measurement, 'X'))
		measurement[current_measurement_count++] = stoul(current_measurement);
	try
	{
		evidence = Evidence(id, measurement, stof(clarity_level_string), stoul(quantity_string), photograph);
		SimpleEvidenceValidator().Validate(evidence);
	}
	catch (EvidenceValidator::InvalidEvidenceException&)
	{
		in.setstate(istream::failbit);
		evidence = Evidence();
	}
	catch (exception&)
	{
		evidence = Evidence();
	}
	return in;
}

ostream& operator<<(ostream& out, const Evidence& evidence)
{
	out << to_string(evidence);
	return out;
}
