#include "OpenGLRenderer.h"
#include "InputCallback.h"
#include "..\core\Camera.h"
#include "..\core\Player.h"
#include "..\core\Level.h"
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
	BaseTexture = ShaderProgram->GetUniformLocation("BaseColor");
	// Texture 0 will be taken as BaseColor texture
	glUniform1i(BaseTexture, 0);
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

void OpenGLRenderer::Tick(float DeltaTime)
{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	CameraPerspectiveMatrix = GetPlayer()->GetCurrentCamera()->GetCameraPerspectiveMatrix(ScreenRatio);

	std::vector<CSceneObject> ObjectsToRender = GetLevel()->GetSceneObjects();
	for (CSceneObject Object : ObjectsToRender)
	{
		std::vector<uint64_t> Models = Object.GetObjectsModels();
		glm::mat4 ModelMatrix = Object.GetModelMatrix();
		for (uint64_t ModelID : Models)
		{
			CModel* Model = GetAssetManager().GetModel(ModelID);
			glm::mat4 LocalToProjectionSpaceMatrix = CameraPerspectiveMatrix * ModelMatrix;
			glUniformMatrix4fv(CameraPerspectiveMatrixLocation, 1, GL_FALSE, glm::value_ptr(LocalToProjectionSpaceMatrix));

			GLuint VAO;
			auto MapIter = Meshes.find(Model->GetMesh());
			if (MapIter != Meshes.end())
			{
				VAO = MapIter->second;
			}
			else
			{
				VAO = LoadMeshToVideomemory(Model->GetMesh());
			}
			glBindVertexArray(VAO);

			if (Model->HasMaterial())
			{
				CMaterial* Material = GetAssetManager().GetMaterial(Model->GetMaterial());
				uint64_t Base = Material->GetBaseColor();
				if (Base)
				{
					auto TextIter = Textures.find(Base);
					if (TextIter != Textures.end())
					{	
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, TextIter->second);
					}
					else
					{
						GLuint Texture = LoadTextureToVideomemory(Base);
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, Texture);
					}
				}
			}

			glDrawElements(GL_TRIANGLES, GetAssetManager().GetMesh(Model->GetMesh())->GetIndicesSize(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	glfwSwapBuffers(window);		
	glfwPollEvents();
}

void OpenGLRenderer::GetScreenSize(int* width, int* height)
{
	glfwGetFramebufferSize(window, width, height);
}

bool OpenGLRenderer::IsAssetLoaded(uint64_t AssetID)
{
	if ((Meshes.count(AssetID) >  0) || (Textures.count(AssetID) > 0))
	{
		return true;
	}
	return false;
}

OpenGLRenderer& OpenGLRenderer::GetRenderer()
{
	static OpenGLRenderer Renderer;
	return Renderer;
}

GLuint OpenGLRenderer::LoadMeshToVideomemory(uint64_t MeshID)
{
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	CMesh* Mesh = GetAssetManager().GetMesh(MeshID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Mesh->GetVerticesSize(), Mesh->GetVertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh->GetIndicesSize(), Mesh->GetIndices(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, NormalX));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TextureCoordinateX));

	Meshes.emplace(MeshID, VAO);
	glBindVertexArray(0);
	return VAO;
}

GLuint OpenGLRenderer::LoadTextureToVideomemory(uint64_t TextureID)
{
	CTexture* Texture = GetAssetManager().GetTexture(TextureID);

	// Generating ID for a texture
	GLuint TextureLoc;
	glGenTextures(1, &TextureLoc);

	// Binding new texture to work with it
	glBindTexture(GL_TEXTURE_2D, TextureLoc);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Loading data to bound texture
	const unsigned char* Pixels = Texture->GetPixels();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (Texture->GetNumChannels() == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texture->GetWidth(), Texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, Pixels);
	}
	else if (Texture->GetNumChannels() == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture->GetWidth(), Texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Pixels);
	}
	Textures.emplace(TextureID, TextureLoc);
	return TextureLoc;
}
