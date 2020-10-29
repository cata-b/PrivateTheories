#pragma once
#include "SeniorClearanceController.h"
#include "StandardClearanceController.h"
#include "FileRepository.h"
#include "HTMLRepository.h"
#include "InMemoryRepository.h"
#include "DatabaseRepository.h"

class UI
{
private:
	SeniorClearanceController* _senior_clearance_controller;
	StandardClearanceController* _standard_clearance_controller;
public:
	UI(SeniorClearanceController* seniorClearanceController, StandardClearanceController* standardClearanceController);
	void Start();
	~UI();
};
