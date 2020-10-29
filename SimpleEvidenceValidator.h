#pragma once
#include "EvidenceValidator.h"

class SimpleEvidenceValidator : public EvidenceValidator
{
public:
	void Validate(const Evidence& Evidence) const override;

	~SimpleEvidenceValidator()
	{
	};
};
