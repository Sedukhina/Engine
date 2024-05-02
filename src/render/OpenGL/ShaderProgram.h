#pragma once
#include <GL/glew.h>
#include "filesystem"

class CShaderProgram {
private:
	GLuint Program;
public:
	CShaderProgram() = delete;
	CShaderProgram(std::filesystem::path pathToVertex, std::filesystem::path pathToFragment);

	void Use();
	GLint GetUniformLocation(const char* name);
};