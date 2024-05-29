#pragma once

#include "../IRenderer.h"

// OpenGL Extension Wrangler Library
#include <GL/glew.h>
// Windowing library
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

class OpenGLRenderer : public IRenderer
{
public:
	virtual bool StartUp() override;
	virtual void ShutDown() override;
	virtual bool ShouldClose() override;
	virtual void SetShouldCloseTrue() override;
	virtual void Tick(float DeltaTime) override;

	virtual void GetScreenSize(int* width, int* height) override;

	virtual bool IsAssetLoaded(uint64_t AssetID) override;

	static OpenGLRenderer& GetRenderer();

private:
	GLFWwindow* window;
	CShaderProgram* ShaderProgram;

	// Uniforms for shaders
	GLint CameraPerspectiveMatrixLocation; 
	GLint BaseTexture;
	
	// Updates when tick
	glm::mat4 CameraPerspectiveMatrix;

	// TEMP (TRANSFER TO SETTINGS THEN)
	float ScreenRatio;

	//virtual void RenderModel(uint64_t Model);

	GLuint LoadMeshToVideomemory(uint64_t Mesh);
	GLuint LoadTextureToVideomemory(uint64_t Texture);

	std::map<uint64_t, GLuint> Meshes;
	std::map<uint64_t, GLuint> Textures;
};