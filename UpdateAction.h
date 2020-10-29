#pragma once
#include "Action.h"

class UpdateAction : public Action
{
private:
	Repository& _repository;
	Evidence _old_evidence, _new_evidence;
public:
	UpdateAction(Repository& Repository, const Evidence& OldEvidence, const Evidence& NewEvidence);
	void ExecuteUndo() override;
	void ExecuteRedo() override;
};
