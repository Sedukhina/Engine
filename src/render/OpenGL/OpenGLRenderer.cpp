#include "OpenGLRenderer.h"
#include "InputCallback.h"

bool OpenGLRenderer::StartUp()
{
	// Window setting section
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	window = glfwCreateWindow(mode->width, mode->height, "Engine", nullptr, nullptr);
	if (window == nullptr)
	{
		LOG_FATAL("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Setting Input Section
	glfwSetKeyCallback(window, InputCallback::key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOG_FATAL("Failed to initialize GLEW");
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	LOG_INFO("Renderer succesfully started up");
	return true;
}

void OpenGLRenderer::ShutDown()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	LOG_INFO("Renderer succesfully shutted down");
}

bool OpenGLRenderer::ShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void OpenGLRenderer::SetShouldCloseTrue()
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}

void OpenGLRenderer::Tick()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);		
	glfwPollEvents();
}

OpenGLRenderer& OpenGLRenderer::GetRenderer()
{
	static OpenGLRenderer Renderer;
	return Renderer;
}
