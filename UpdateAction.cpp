#include "UpdateAction.h"
#include <exception>

UpdateAction::UpdateAction(Repository& Repository, const Evidence& OldEvidence, const Evidence& NewEvidence) :
	_repository(Repository), _old_evidence(OldEvidence), _new_evidence(NewEvidence)
{
	if (_old_evidence.ID() != _new_evidence.ID())
		throw std::exception("Invalid creation of UpdateAction: differrent IDs.");
}

void UpdateAction::ExecuteUndo()
{
	_repository.UpdateEvidence(_old_evidence);
}

void UpdateAction::ExecuteRedo()
{
	_repository.UpdateEvidence(_new_evidence);
}
