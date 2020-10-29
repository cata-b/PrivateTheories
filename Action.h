#include "Repository.h"
#include "Evidence.h"
#pragma once
class Action
{
public:
	virtual void ExecuteUndo() = 0;
	virtual void ExecuteRedo() = 0;

	virtual ~Action()
	{
	};
};
