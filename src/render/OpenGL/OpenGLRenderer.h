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
	virtual void Tick() override;

	virtual void GetScreenSize(int* width, int* height) override;

	static OpenGLRenderer& GetRenderer();
private:
	GLFWwindow* window;
	CShaderProgram* ShaderProgram;

	// Uniforms for shaders
	GLint CameraPerspectiveMatrixLocation; 
	
	// Updates when tick
	glm::mat4 CameraPerspectiveMatrix;

	// TEMP (TRANSFER TO SETTINGS THEN)
	float ScreenRatio;
};