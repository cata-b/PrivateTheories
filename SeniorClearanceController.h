#pragma once
#include "Repository.h"
#include "Evidence.h"
#include "Action.h"
#include <string>
#include <vector>

class SeniorClearanceController
{
private:

	std::vector<std::unique_ptr<Action>>& _undo_stack;
	std::vector<std::unique_ptr<Action>>& _redo_stack;

	/// <summary>
	/// The underlying Repository.
	/// </summary>
	Repository* _repository;

	/// <summary>
	/// Adds an Evidence to the Repository.
	/// </summary>
	/// <param name="Evidence">The Evidence to be added.</param>
	/// <returns>0 for success, -1 for fail</returns>
	void _add_evidence(const Evidence& Evidence);

	/// <summary>
	/// Updates an Evidence.
	/// </summary>
	/// <param name="Evidence">Evidence to replace the one with the same ID.</param>
	/// <returns>0 for success, 1 for fail</returns>
	void _update_evidence(const Evidence& Evidence);

	/// <summary>
	/// Deletes an Evidence.
	/// </summary>
	/// <param name="EvidenceID">The ID of the Evidence.</param>
	/// <returns>0 for success, 1 for fail</returns>
	void _delete_evidence(std::string EvidenceID);

	/// <summary>
	/// Lists all Evidence instances from the Repository.
	/// </summary>
	/// <returns>All data as a string.</returns>
	std::vector<Evidence>& _list_evidence();

public:
	static const int SUCCESS_MESSAGE;
	static const int LIST_MESSAGE;

	struct CommandResult
	{
		int Message = SUCCESS_MESSAGE;
		std::vector<Evidence>* Data = nullptr;
	};

	/// <summary>
	/// Creates a new SeniorClearanceController that uses an existing Repository.
	/// </summary>
	/// <param name="repository">The underlying Repository.</param>
	SeniorClearanceController(Repository* repository, std::vector<std::unique_ptr<Action>>& UndoStack,
	                          std::vector<std::unique_ptr<Action>>& RedoStack);

	/// <summary>
	/// Runs a command.
	/// </summary>
	/// <param name="Command">The command to Start</param>
	/// <returns>A MESSAGE or what to print</returns>
	CommandResult& RunCommand(const std::string& Command);

	~SeniorClearanceController();

	class SeniorClearanceControllerException : public std::exception
	{
	private:
		std::string _message;
	public:
		explicit SeniorClearanceControllerException(const std::string& message) noexcept;
		const char* what() const override;
	};
};
