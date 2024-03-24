#include "InputScheme.h"

#include "..\Logger.h"

void InputScheme::BindInputAction(InputActionFunction func, InputKey key, InputAction action)
{
	BindedActions[action * InputKey::LAST_KEY_VALUE + key].emplace_back(func);
}

void InputScheme::BindInputAction(InputActionFunction func, int key, int action)
{
	if (key >= 0 && InputKey::LAST_KEY_VALUE >= key && action >= 0 && InputAction::LAST_ACTION_VALUE >= action)
	{
		InputScheme::BindInputAction(func, static_cast<InputKey>(key), static_cast<InputAction>(action));
	}
}

void InputScheme::InvokeAction(InputKey key, InputAction action)
{
	for (std::function<void()> Action : BindedActions[action * InputKey::LAST_KEY_VALUE + key])
	{
		std::invoke(Action);
	}
}
