#pragma once
#include "Evidence.h"

class EvidenceValidator
{
public:
	virtual void Validate(const Evidence& Evidence) const = 0;

	virtual ~EvidenceValidator()
	{
	};

	class InvalidEvidenceException : public std::exception
	{
	private:
		std::string _message;
		Evidence& _evidence;
	public:
		InvalidEvidenceException(std::string message, const Evidence& evidence) : _message(message),
		                                                                          _evidence(*new Evidence(evidence))
		{
		}

		const char* what() const override { return _message.c_str(); }
		virtual const Evidence& GetEvidence() const { return _evidence; }
		virtual ~InvalidEvidenceException() { delete&_evidence; }
	};
};
