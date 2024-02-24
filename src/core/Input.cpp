#include "Input.h"

Input& Input::GetInput()
{
	static Input InputInstance;
	return InputInstance;
}

void Input::HandleInput(InputKey Key, InputAction Action)
{

}
