#include "SimpleEvidenceValidator.h"

void SimpleEvidenceValidator::Validate(const Evidence& Evidence) const
{
	if (!(Evidence.ImageClarityLevel() >= 0 &&
		Evidence.MeasurementX() > 0 && Evidence.MeasurementY() >= 0 && Evidence.MeasurementZ() >= 0 &&
		Evidence.Quantity() >= 1))
		throw InvalidEvidenceException("Invalid evidence.", Evidence);
}
