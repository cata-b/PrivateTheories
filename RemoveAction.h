#pragma once
#include "Action.h"

class RemoveAction : public Action
{
private:
	Repository& _repository;
	Evidence _evidence;
public:
	RemoveAction(Repository& Repository, const Evidence& Evidence);
	void ExecuteUndo() override;
	void ExecuteRedo() override;
};
