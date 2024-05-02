#include "OpenGLRenderer.h"
#include "InputCallback.h"
#include "..\core\Camera.h"
#include "..\core\Player.h"
#include "..\core\core.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

bool OpenGLRenderer::StartUp()
{
	// Window setting section
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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

	/*Setting Viewport size*/
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);

	// Global OpenGL Settings
	glEnable(GL_DEPTH_TEST);

	// Creating Shader Program
	ShaderProgram = &CShaderProgram("/render/Shaders/OGL_Shaders/Shader.vert", "/render/Shaders/OGL_Shaders/Shader.frag");
	CameraPerspectiveMatrixLocation = ShaderProgram->GetUniformLocation("CameraPerspectiveMatrix");
	ShaderProgram->Use();

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
	glClearColor(0.0f, 0.2f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/// TEMP BLOCK 
	glm::mat4 model_matrix(1);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glm::mat4 CameraPerspectiveMatrix = GetPlayer()->GetCurrentCamera()->GetCameraPerspectiveMatrix(((GLfloat)screenWidth / (GLfloat)screenHeight));

	glm::mat4 LocalToProjectionSpaceMatrix = CameraPerspectiveMatrix * model_matrix;

	glUniformMatrix4fv(CameraPerspectiveMatrixLocation, 1, GL_FALSE, glm::value_ptr(CameraPerspectiveMatrix));

	float vertices[] = {
		-1.f, 0.f, -1.f,  
		-1.f, 0.f, 1.f,
		1.f, 0.f, -1.f,
		1.f, 0.f, 1.f,
		0.f, 3.f, 0.f
	};

	int indices[] = {
		0, 1, 2,
		3, 1, 2,
		0, 1, 4,
		0, 2, 4,
		3, 1, 4,
		3, 2, 4
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
	/// END OF TEMP BLOCK


	glfwSwapBuffers(window);		
	glfwPollEvents();
}

OpenGLRenderer& OpenGLRenderer::GetRenderer()
{
	static OpenGLRenderer Renderer;
	return Renderer;
}
