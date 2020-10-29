#include "InMemoryRepository.h"
#include <exception>
#include <string>
#include "SetDebugNew.h"
using namespace std;

vector<Evidence>::iterator InMemoryRepository::_search_id(const string& id) const
{
	if (_data.size() == 0)
		return _data.end();
	//unsigned int measurements[3]{ 0, 0, 0 };
	Evidence searched = Evidence(/*id, measurements, 0.0f, (unsigned int)0, string("")*/);
	auto result = lower_bound(_data.begin(), _data.end(), searched, [id](Evidence first, const Evidence& second)
	{
		return first.ID() < id;
	});
	return (result == _data.end() ? result - 1 : result);
}

InMemoryRepository::InMemoryRepository(const EvidenceValidator& Validator) : _data(*new vector<Evidence>()),
                                                                             _validator(Validator)
{
}

InMemoryRepository::InMemoryRepository(vector<Evidence>& data, const EvidenceValidator& Validator) : _data(data),
                                                                                                     _validator(
	                                                                                                     Validator)
{
}


int InMemoryRepository::Size() const { return _data.size(); }

void InMemoryRepository::AddEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	if (_data.size() == 0)
	{
		_data.push_back(evidence);
		return;
	}
	const string& evidence_id = evidence.ID();
	auto position = _search_id(evidence_id);
	if (position->ID() == evidence_id)
		throw RepositoryException("Duplicate ID");
	_data.insert(position->ID() < evidence_id ? position + 1 : position, evidence);
}

Evidence InMemoryRepository::RemoveEvidence(std::string evidence_id)
{
	if (_data.size() == 0)
		throw RepositoryException("No evidence to remove");
	auto position = _search_id(evidence_id);
	if (position->ID() != evidence_id)
		throw RepositoryException("ID not found");
	Evidence removed(*position);
	_data.erase(position);
	return removed;
}

Evidence InMemoryRepository::UpdateEvidence(const Evidence& evidence)
{
	_validator.Validate(evidence);
	if (_data.size() == 0)
		throw RepositoryException("No evidence to update");
	auto position = _search_id(evidence.ID());
	if (position->ID() != evidence.ID())
		throw RepositoryException("ID not found");
	Evidence removed(*position);
	*position = evidence;
	return removed;
}

Evidence InMemoryRepository::AtIndex(int index) const { return _data[index]; }

Evidence InMemoryRepository::AtID(std::string evidence_id) const
{
	auto position = _search_id(evidence_id);
	if (position != _data.end() && position->ID() == evidence_id)
		return *position;
	throw RepositoryException("Missing ID");
}

void InMemoryRepository::OpenFile() const
{
	throw RepositoryException("Current repository is in memory.");
}

InMemoryRepository::~InMemoryRepository()
{
	delete&_data;
	delete&_validator;
}
