#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "..\core\core.h"

namespace InputCallback
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GetInputController().HandleInput(key, action);
	}
}