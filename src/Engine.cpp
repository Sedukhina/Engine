#include "Engine.h"

bool Engine::StartUp()
{
	LOG_INFO("Engine succesfully started up");
	GetRenderer().StartUp();
	Mainloop();
	return 0;
}

void Engine::ShutDown()
{
	GetRenderer().ShutDown();
	LOG_INFO("Engine succesfully shutted down");
}

void Engine::Mainloop()
{
	int x = 10;
	while (x > 0)
	{
		LOG_INFO("Working properly");
		x--;
	}
}

CRenderer& Engine::GetRenderer()
{
	static CRenderer Renderer;
	return Renderer;
}
