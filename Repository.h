#pragma once
#include "Evidence.h"
#include <iostream>

class Repository
{
public:
	/// <summary>
	/// Gets the number of Evidence instances contained.
	/// </summary>
	virtual int Size() const = 0;

	/// <summary>
	/// Adds an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>0 for success, -1 for fail.</returns>
	virtual void AddEvidence(const Evidence& evidence) = 0;

	/// <summary>
	/// Removes an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>Pointer to the removed Evidence on success, nullptr on fail.</returns>
	virtual Evidence RemoveEvidence(std::string evidence_id) = 0;

	/// <summary>
	/// Updates an Evidence instance.
	/// </summary>
	/// <param name="evidence">Valid Evidence instance.</param>
	/// <returns>Pointer to the old Evidence on success, nullptr on fail.</returns>
	virtual Evidence UpdateEvidence(const Evidence& evidence) = 0;

	/// <summary>
	/// Gets a const reference to the Evidence at the given Index.
	/// </summary>
	virtual Evidence AtIndex(int index) const = 0;

	/// <summary>
	/// Gets a const reference to the Evidence that has the given ID.
	/// </summary>
	virtual Evidence AtID(std::string evidence_id) const = 0;

	virtual void OpenFile() const = 0;

	virtual ~Repository()
	{
	};

	class RepositoryException : public std::exception
	{
	private:
		std::string _message;
	public:
		explicit RepositoryException(std::string message) : _message(message)
		{
		};
		const char* what() const override { return _message.c_str(); }
	};
};
