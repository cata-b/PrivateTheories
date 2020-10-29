#include "RemoveAction.h"

RemoveAction::RemoveAction(Repository& Repository, const Evidence& Evidence) : _repository(Repository),
                                                                               _evidence(Evidence)
{
}

void RemoveAction::ExecuteUndo()
{
	_repository.AddEvidence(_evidence);
}

void RemoveAction::ExecuteRedo()
{
	_repository.RemoveEvidence(_evidence.ID());
}
