#include "UI.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "SetDebugNew.h"
using namespace std;

string get_file_extension(const string& file_name)
{
	auto dot_position = file_name.find_last_of('.');
	if (dot_position != string::npos)
		return file_name.substr(dot_position + 1);
	return "";
}

UI::UI(SeniorClearanceController* seniorClearanceController, StandardClearanceController* standardClearanceController)
	: _senior_clearance_controller(seniorClearanceController),
	  _standard_clearance_controller(standardClearanceController)
{
}

void UI::Start()
{
	string command;
	char mode = 'C';
	while (true)
	{
		getline(cin, command);
		if (command == "") continue;
		if (command.back() == '\n')
			command.pop_back();
		if (command == "mode A")
		{
			mode = 'A';
			continue;
		}
		if (command == "mode B")
		{
			mode = 'B';
			continue;
		}
		if (command == "exit")
			break;
		if (mode == 'A')
		{
			try
			{
				SeniorClearanceController::CommandResult& command_result = _senior_clearance_controller->
					RunCommand(command);
				if (command_result.Message == SeniorClearanceController::LIST_MESSAGE)
				{
					for (auto evidence : (*command_result.Data))
						std::cout << to_string(evidence) << "\n";
					delete command_result.Data;
					delete&command_result;
					continue;
				}
				if (command_result.Message == SeniorClearanceController::SUCCESS_MESSAGE)
				{
					delete&command_result;
				}
			}
			catch (exception& error)
			{
				std::cout << error.what() << "\n";
			}
		}
		else if (mode == 'B')
		{
			try
			{
				StandardClearanceController::CommandResult& command_result = _standard_clearance_controller->
					RunCommand(command);
				if (command_result.Message == StandardClearanceController::MULTIPLE_EVIDENCE_RESULT_MESSAGE)
				{
					for (auto evidence : (*command_result.ListResult))
						std::cout << to_string(evidence) << "\n";
					delete command_result.ListResult;
					delete&command_result;
				}
				if (command_result.Message == StandardClearanceController::SINGLE_EVIDENCE_RESULT_MESSAGE)
				{
					std::cout << to_string(*(command_result.SingleEvidenceResult)) << "\n";
					delete command_result.SingleEvidenceResult;
					delete&command_result;
				}
				if (command_result.Message == StandardClearanceController::SUCCESS_MESSAGE)
				{
					delete&command_result;
				}
			}
			catch (exception& error)
			{
				std::cout << error.what() << "\n";
			}
		}
		else
		{
			cout << "No mode selected! Use \"mode A\" or \"mode B\".";
		}
	}
}

UI::~UI()
{
	delete _senior_clearance_controller;
	delete _standard_clearance_controller;
}
