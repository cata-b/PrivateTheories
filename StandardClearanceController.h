#pragma once
#include "Repository.h"
#include "Action.h"
#include <string>
#include <vector>

class StandardClearanceController
{
private:
	Repository *_repository, *_user_repository;
	std::vector<Evidence>* _filter_data;
	std::vector<Evidence>::const_iterator _filter_begin;
	std::vector<Evidence>::const_iterator _filter_end;
	std::vector<std::unique_ptr<Action>>& _undo_stack;
	std::vector<std::unique_ptr<Action>>& _redo_stack;

	void _reset_filter();

	const Evidence& _next();
	void _save_id(std::string ID);
	const Evidence& _filter(unsigned int measurement[3], unsigned int minimum_quantity);
public:
	StandardClearanceController(Repository* repository, Repository* UserRepository,
	                            std::vector<std::unique_ptr<Action>>& UndoStack,
	                            std::vector<std::unique_ptr<Action>>& RedoStack);

	static const int SINGLE_EVIDENCE_RESULT_MESSAGE;
	static const int MULTIPLE_EVIDENCE_RESULT_MESSAGE;
	static const int SUCCESS_MESSAGE;

	struct CommandResult
	{
		int Message;
		const Evidence* SingleEvidenceResult;
		std::vector<Evidence>* ListResult;
	};

	CommandResult& RunCommand(const std::string& Command);
	~StandardClearanceController();

	class StandardClearanceControllerException : public std::exception
	{
	private:
		std::string _message;
	public:
		explicit StandardClearanceControllerException(const std::string& message) noexcept;
		const char* what() const override;
	};
};
