#include "core.h"
#include "render/Renderer.h"

class Engine
{
public:
	Engine() {};
	~Engine() {};

	bool StartUp();
	void ShutDown();

private:
	void Mainloop();

	static CRenderer& GetRenderer();
};

