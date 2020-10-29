#include "AddAction.h"

AddAction::AddAction(Repository& Repository, const Evidence& Evidence) : _repository(Repository), _evidence(Evidence)
{
}

void AddAction::ExecuteUndo()
{
	_repository.RemoveEvidence(_evidence.ID());
}

void AddAction::ExecuteRedo()
{
	_repository.AddEvidence(_evidence);
}
