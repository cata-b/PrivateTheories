#pragma once
#include "Evidence.h"
#include "Repository.h"
#include "EvidenceValidator.h"
#include "SimpleEvidenceValidator.h"
#include <vector>

class InMemoryRepository : public Repository
{
private:
	std::vector<Evidence>& _data;
	const EvidenceValidator& _validator;
	/// <summary>
	/// Binary search by Evidence ID
	/// </summary>
	std::vector<Evidence>::iterator _search_id(const std::string& id) const;

public:
	/// <summary>
	/// Creates an empty InMemoryRepository instance.
	/// </summary>
	InMemoryRepository(const EvidenceValidator& Validator = *new SimpleEvidenceValidator());

	/// <summary>
	/// Creates a InMemoryRepository that uses an existing Dynamicvector.
	/// </summary>
	InMemoryRepository(std::vector<Evidence>& data,
	                   const EvidenceValidator& Validator = *new SimpleEvidenceValidator());

	/// <summary>
	/// Gets the number of Evidence instances contained.
	/// </summary>
	int Size() const override;

	/// <summary>
	/// Adds an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>0 for success, -1 for fail.</returns>
	void AddEvidence(const Evidence& evidence) override;

	/// <summary>
	/// Removes an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>Pointer to the removed Evidence on success, nullptr on fail.</returns>
	Evidence RemoveEvidence(std::string evidence_id) override;

	/// <summary>
	/// Updates an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>Pointer to the old Evidence on success, nullptr on fail.</returns>
	Evidence UpdateEvidence(const Evidence& evidence) override;

	/// <summary>
	/// Gets a const reference to the Evidence at the given Index.
	/// </summary>
	Evidence AtIndex(int index) const override;

	/// <summary>
	/// Gets a const reference to the Evidence that has the given ID.
	/// </summary>
	Evidence AtID(std::string evidence_id) const override;

	void OpenFile() const override;

	~InMemoryRepository();
};
