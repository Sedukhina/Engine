#include "OpenGLRenderer.h"
#include "InputCallback.h"
#include "..\core\Camera.h"
#include "..\core\Player.h"
#include "..\core\core.h"
#include "..\core\AssetManager\AssetManager.h"
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
	window = glfwCreateWindow(mode->width, mode->height, "Engine", glfwGetPrimaryMonitor(), nullptr);
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
	ScreenRatio = (GLfloat)screenWidth / (GLfloat)screenHeight;

	// Global OpenGL Settings
	glEnable(GL_DEPTH_TEST);

	// Creating Shader Program
	ShaderProgram = &CShaderProgram("/render/Shaders/OGL_Shaders/Shader.vert", "/render/Shaders/OGL_Shaders/Shader.frag");
	CameraPerspectiveMatrixLocation = ShaderProgram->GetUniformLocation("CameraPerspectiveMatrix");
	ShaderProgram->Use();

	CameraPerspectiveMatrix = glm::mat4(1);

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
	
	CameraPerspectiveMatrix = GetPlayer()->GetCurrentCamera()->GetCameraPerspectiveMatrix(ScreenRatio);

	/// TEMP BLOCK 
	glm::mat4 model_matrix(1);
	glm::mat4 LocalToProjectionSpaceMatrix = CameraPerspectiveMatrix * model_matrix;

	glUniformMatrix4fv(CameraPerspectiveMatrixLocation, 1, GL_FALSE, glm::value_ptr(CameraPerspectiveMatrix));

	CMesh* Mesh = GetAssetManager().GetMesh();

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Mesh->GetVerticesSize(), Mesh->GetVertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh->GetIndicesSize(), Mesh->GetIndices(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glDrawElements(GL_TRIANGLES, Mesh->GetIndicesSize(), GL_UNSIGNED_INT, 0);
	/// END OF TEMP BLOCK


	glfwSwapBuffers(window);		
	glfwPollEvents();
}

void OpenGLRenderer::GetScreenSize(int* width, int* height)
{
	glfwGetFramebufferSize(window, width, height);
}

OpenGLRenderer& OpenGLRenderer::GetRenderer()
{
	static OpenGLRenderer Renderer;
	return Renderer;
}
