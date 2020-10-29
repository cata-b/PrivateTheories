#pragma once
#include "Action.h"

class AddAction : public Action
{
private:
	Repository& _repository;
	Evidence _evidence;
public:
	AddAction(Repository& Repository, const Evidence& Evidence);
	void ExecuteUndo() override;
	void ExecuteRedo() override;
};
