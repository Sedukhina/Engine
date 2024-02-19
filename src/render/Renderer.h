#ifdef VULKAN
	class VulkanRenderer;
#else
	#include "OpenGL/OpenGLRenderer.h"
	typedef OpenGLRenderer CRenderer;
#endif