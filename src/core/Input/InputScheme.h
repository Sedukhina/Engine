#pragma once

#include <array>
#include <vector>
#include "InputComponent.h"

// GLFW SCHEME COPY!!!
enum InputAction
{
	RELEASED,
	PRESSED,
	REPEATED,
	LAST_ACTION_VALUE = REPEATED
};

enum InputKey
{
	// Alphabet based on ASCII
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	ESC = 256,
	LAST_KEY_VALUE = ESC
};
#pragma once

class InputScheme
{
public:
	InputScheme() { BindedActions.fill(std::vector<InputActionFunction>{ }); };
	~InputScheme() {};

	// Use std::bind to make first argument: std::bind(&InputComponent::ActionToBind, this)
	void BindInputAction(InputActionFunction func, InputKey key, InputAction action);
	void BindInputAction(InputActionFunction func, int key, int action);
	void InvokeAction(InputKey key, InputAction action);


private:
	// Functions to invoke (ONLY VOID RETURN)
	// ARRAY[Action_num] contains ARRAY[Input_keys_num] contains vector of refernces to InputController methods invoked by certain action and key  
	std::array<std::vector<InputActionFunction>, InputKey::LAST_KEY_VALUE * (InputAction::LAST_ACTION_VALUE + 1) +1> BindedActions;
};
