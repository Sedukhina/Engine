#include "InputController.h"

void CInputController::HandleInput(int Key, int Action)
{
	if (Key >= 0 && InputKey::LAST_KEY_VALUE>= Key && Action >= 0 && InputAction::LAST_ACTION_VALUE >= Action)
	{
		CurrentInputScheme.InvokeAction(static_cast<InputKey>(Key), static_cast<InputAction>(Action));
	}
}

CInputController& GetInputController()
{
	static CInputController InputInstance;
	return InputInstance;
}