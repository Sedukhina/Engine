#pragma once

#include "InputScheme.h"

// Class for handling input
class CInputController
{
public:
	CInputController() { CurrentInputScheme = InputScheme(); };
	~CInputController() {};

	__declspec(dllexport) void HandleInput(int Key, int Action);
	InputScheme* GetCurrentInputScheme() { return &CurrentInputScheme; };
private:
	InputScheme CurrentInputScheme;
};

__declspec(dllexport) CInputController& GetInputController();