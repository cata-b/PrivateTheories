#pragma once
#include "Repository.h"
#include "EvidenceValidator.h"
#include "SimpleEvidenceValidator.h"

class HTMLRepository : public Repository
{
private:
	int _size;
	std::string _file;
	const EvidenceValidator& _validator;
	void _write_file_begin(std::ostream& out);
	void _write_file_end(std::ostream& out);
	Evidence _move_evidence_until_ID(std::istream& in, std::ostream& out, std::string ID,
	                                 std::istringstream& table_data);
	void _copy_data(std::istream& table_data, std::ostream& out);
	std::string _evidence_to_html(const Evidence& Evidence);
public:
	HTMLRepository(std::string file, const EvidenceValidator& Validator = *new SimpleEvidenceValidator());

	int Size() const override;

	void AddEvidence(const Evidence& evidence) override;

	Evidence RemoveEvidence(std::string evidence_id) override;

	Evidence UpdateEvidence(const Evidence& evidence) override;

	Evidence AtIndex(int index) const override;

	Evidence AtID(std::string evidence_id) const override;

	void SetFile(std::string file);

	void OpenFile() const override;

	~HTMLRepository();
};
