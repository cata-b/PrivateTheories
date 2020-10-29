#include "StandardClearanceController.h"
#include "AddAction.h"
#include <sstream>
#include "SetDebugNew.h"
using namespace std;

const int StandardClearanceController::SINGLE_EVIDENCE_RESULT_MESSAGE = 1;
const int StandardClearanceController::MULTIPLE_EVIDENCE_RESULT_MESSAGE = 2;
const int StandardClearanceController::SUCCESS_MESSAGE = 0;

void StandardClearanceController::_reset_filter()
{
	delete _filter_data;
	_filter_data = new vector<Evidence>();
	for (int i = 0; i < _repository->Size(); i++)
		_filter_data->push_back(_repository->AtIndex(i));
	_filter_begin = _filter_data->begin();
	_filter_end = _filter_data->end();
}

const Evidence& StandardClearanceController::_next()
{
	if (_filter_begin == _filter_end)
		_reset_filter();
	return *(_filter_begin++);
}

void StandardClearanceController::_save_id(std::string ID)
{
	const Evidence& found = _repository->AtID(ID);
	_user_repository->AddEvidence(found);
	_undo_stack.push_back(move(make_unique<AddAction>(*_user_repository, found)));
	_redo_stack.clear();
}

const Evidence& StandardClearanceController::_filter(unsigned int measurement[3], unsigned int minimum_quantity)
{
	delete _filter_data;
	_filter_data = new vector<Evidence>();
	for (int i = 0; i < _repository->Size(); i++)
	{
		const Evidence& current = _repository->AtIndex(i);
		if (current.MeasurementX() == measurement[0] &&
			current.MeasurementY() == measurement[1] &&
			current.MeasurementZ() == measurement[2] &&
			current.Quantity() >= minimum_quantity)
			_filter_data->push_back(current);
	}
	_filter_begin = _filter_data->begin();
	_filter_end = _filter_data->end();
	return _next();
}

StandardClearanceController::StandardClearanceController(Repository* repository, Repository* UserRepository,
                                                         vector<unique_ptr<Action>>& UndoStack,
                                                         vector<unique_ptr<Action>>& RedoStack) :
	_repository(repository),
	_user_repository(UserRepository),
	_filter_data(nullptr),
	_filter_begin(),
	_filter_end(),
	_undo_stack(UndoStack),
	_redo_stack(RedoStack)
{
}

StandardClearanceController::CommandResult& StandardClearanceController::RunCommand(const std::string& Command)
{
	istringstream command_line(Command);
	string command_word;
	CommandResult& result = *new CommandResult;
	command_line >> command_word;
	if (command_word == "open")
	{
		_user_repository->OpenFile();
		result.Message = SUCCESS_MESSAGE;
		return result;
	}
	if (command_word == "next")
	{
		result.Message = SINGLE_EVIDENCE_RESULT_MESSAGE;
		result.SingleEvidenceResult = new Evidence(_next());
		return result;
	}
	if (command_word == "save")
	{
		string ID;
		command_line >> ID;
		try
		{
			_save_id(ID);
			result.Message = SUCCESS_MESSAGE;
			return result;
		}
		catch (exception&)
		{
			delete&result;
			throw StandardClearanceControllerException("Invalid command.");
		}
	}
	if (command_word == "list")
	{
		string measurement_string;
		unsigned int measurement[3], quantity;
		try
		{
			command_line >> measurement_string >> quantity;
			istringstream measurement_splitter(measurement_string);
			string current_measurement;
			int measurement_index = 0;
			while (measurement_index < 3 && getline(measurement_splitter, current_measurement, 'X'))
				measurement[measurement_index++] = stoul(current_measurement);
			result.Message = SINGLE_EVIDENCE_RESULT_MESSAGE;
			result.SingleEvidenceResult = new Evidence(_filter(measurement, quantity));
			return result;
		}
		catch (exception&)
		{
			delete&result;
			throw StandardClearanceControllerException("Invalid command.");
		}
	}
	if (command_word == "mylist")
	{
		result.Message = MULTIPLE_EVIDENCE_RESULT_MESSAGE;
		result.ListResult = new vector<Evidence>();
		for (int i = 0; i < _user_repository->Size(); i++)
			result.ListResult->push_back(_user_repository->AtIndex(i));
		return result;
	}
	if (command_word == "undo")
	{
		if (_undo_stack.size() > 0)
		{
			auto last_action = move(_undo_stack.back());
			_undo_stack.pop_back();
			last_action.get()->ExecuteUndo();
			_redo_stack.push_back(move(last_action));
			result.Message = SUCCESS_MESSAGE;
			return result;
		}
		delete&result;
		throw StandardClearanceControllerException("Cannot undo.");
	}
	if (command_word == "redo")
	{
		if (_redo_stack.size() > 0)
		{
			auto last_action = move(_redo_stack.back());
			_redo_stack.pop_back();
			last_action.get()->ExecuteRedo();
			_undo_stack.push_back(move(last_action));
			result.Message = SUCCESS_MESSAGE;
			return result;
		}
		delete&result;
		throw StandardClearanceControllerException("Cannot redo.");
	}
	delete&result;
	throw StandardClearanceControllerException("Invalid command.");
}

StandardClearanceController::~StandardClearanceController()
{
	delete _filter_data;
	delete _user_repository;
}

StandardClearanceController::StandardClearanceControllerException::StandardClearanceControllerException(
	const std::string& message) noexcept : _message(message)
{
}

const char* StandardClearanceController::StandardClearanceControllerException::what() const { return _message.c_str(); }
