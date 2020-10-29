#include "SeniorClearanceController.h"
#include "AddAction.h"
#include "RemoveAction.h"
#include "UpdateAction.h"
#include <sstream>
#include "SetDebugNew.h"

using namespace std;

const int SeniorClearanceController::SUCCESS_MESSAGE = 0;
const int SeniorClearanceController::LIST_MESSAGE = 2;

SeniorClearanceController::SeniorClearanceController(Repository* repository, vector<unique_ptr<Action>>& UndoStack,
                                                     vector<unique_ptr<Action>>& RedoStack) :
	_undo_stack(UndoStack), _redo_stack(RedoStack), _repository(repository)
{
};

void SeniorClearanceController::_add_evidence(const Evidence& evidence)
{
	_repository->AddEvidence(evidence);
	_redo_stack.clear();
	_undo_stack.push_back(move(make_unique<AddAction>(*_repository, evidence)));
}

void SeniorClearanceController::_update_evidence(const Evidence& evidence)
{
	Evidence old_evidence = _repository->UpdateEvidence(evidence);
	_redo_stack.clear();
	_undo_stack.push_back(move(make_unique<UpdateAction>(*_repository, old_evidence, evidence)));
}

void SeniorClearanceController::_delete_evidence(string EvidenceID)
{
	Evidence old_evidence = _repository->RemoveEvidence(EvidenceID);
	_redo_stack.clear();
	_undo_stack.push_back(move(make_unique<RemoveAction>(*_repository, old_evidence)));
}

vector<Evidence>& SeniorClearanceController::_list_evidence()
{
	vector<Evidence>& result = *new vector<Evidence>();
	for (int i = 0; i < _repository->Size(); i++)
		result.push_back(_repository->AtIndex(i));
	return result;
}

SeniorClearanceController::CommandResult& SeniorClearanceController::RunCommand(const string& Command)
{
	istringstream command_line(Command);
	string command_word;
	command_line >> command_word;
	CommandResult* command_result = new CommandResult;
	if (command_word == "add")
	{
		string evidence_string;
		getline(command_line, evidence_string);
		Evidence& command_data = *Evidence::FromString(evidence_string);
		try
		{
			_add_evidence(command_data);
			delete&command_data;
		}
		catch (exception&)
		{
			delete&command_data;
			delete command_result;
			throw;
		}
	}
	else if (command_word == "update")
	{
		string evidence_string;
		getline(command_line, evidence_string);
		Evidence& command_data = *Evidence::FromString(evidence_string);
		try
		{
			_update_evidence(command_data);
			delete&command_data;
		}
		catch (exception&)
		{
			delete&command_data;
			delete command_result;
			throw;
		}
	}
	else if (command_word == "delete")
	{
		string evidence_ID;
		command_line >> evidence_ID;
		try
		{
			_delete_evidence(evidence_ID);
		}
		catch (exception&)
		{
			delete command_result;
			throw;
		}
	}
	else if (command_word == "list")
	{
		command_result->Data = &_list_evidence();
		command_result->Message = LIST_MESSAGE;
	}
	else if (command_word == "undo")
	{
		if (_undo_stack.size() > 0)
		{
			auto last_action = move(_undo_stack.back());
			_undo_stack.pop_back();
			last_action.get()->ExecuteUndo();
			_redo_stack.push_back(move(last_action));
			command_result->Message = SUCCESS_MESSAGE;
		}
		else
		{
			delete command_result;
			throw SeniorClearanceControllerException("Cannot undo.");
		}
	}
	else if (command_word == "redo")
	{
		if (_redo_stack.size() > 0)
		{
			auto last_action = move(_redo_stack.back());
			_redo_stack.pop_back();
			last_action.get()->ExecuteRedo();
			_undo_stack.push_back(move(last_action));
			command_result->Message = SUCCESS_MESSAGE;
		}
		else
		{
			delete command_result;
			throw SeniorClearanceControllerException("Cannot redo.");
		}
	}
	else
	{
		delete command_result;
		throw SeniorClearanceControllerException("Invalid command.");
	}

	return *command_result;
}

SeniorClearanceController::~SeniorClearanceController()
{
	delete _repository;
	delete&_undo_stack;
	delete&_redo_stack;
}

SeniorClearanceController::SeniorClearanceControllerException::SeniorClearanceControllerException(
	const std::string& message) noexcept : _message(message)
{
}

const char* SeniorClearanceController::SeniorClearanceControllerException::what() const { return _message.c_str(); }
