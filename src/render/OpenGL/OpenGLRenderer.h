#include "../IRenderer.h"
//Windowing library
#include <GLFW/glfw3.h>

class OpenGLRenderer : public IRenderer
{
public:
	virtual bool StartUp() override;
	virtual void ShutDown() override;
private:
	GLFWwindow* window;
};