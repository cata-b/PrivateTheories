#pragma once
#include "Evidence.h"
#include "EvidenceValidator.h"
#include "SimpleEvidenceValidator.h"
#include "Repository.h"
#include <iostream>

class FileRepository : public Repository
{
private:
	int _size;
	std::string _file;
	const EvidenceValidator& _validator;
	Evidence _move_evidence_until_ID(std::ifstream& original, std::ofstream& temp, std::string ID);
	void _copy_file(std::ifstream& in, std::ofstream& out);
public:
	/// <summary>
	/// Creates a FileRepository that uses a specified file.
	/// </summary>
	FileRepository(std::string file = tmpnam(nullptr),
	               const EvidenceValidator& Validator = *new SimpleEvidenceValidator());

	int Size() const override;

	void AddEvidence(const Evidence& evidence) override;

	Evidence RemoveEvidence(std::string evidence_id) override;

	Evidence UpdateEvidence(const Evidence& evidence) override;

	Evidence AtIndex(int index) const override;

	Evidence AtID(std::string evidence_id) const override;

	/// <summary>
	/// Sets the file for the FileRepository.
	/// </summary>
	/// <param name="file">name of the file</param>
	void SetFile(std::string file);

	void OpenFile() const override;

	~FileRepository();
};
