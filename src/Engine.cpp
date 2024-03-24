#include "Engine.h"
#include <time.h>
#include <cstdio>

bool Engine::StartUp()
{
	auto Controller = GetInputController();
	LOG_INFO("Input Controller Initialized");
	if (!CRenderer::GetRenderer().StartUp())
	{
		return 0;
	}
	LOG_INFO("Engine succesfully started up");
	Mainloop();
	return 1;
}

void Engine::ShutDown()
{
	CRenderer::GetRenderer().ShutDown();
	LOG_INFO("Engine succesfully shutted down");
}

void Engine::Mainloop()
{
	clock_t time_from_start = clock();
	char buffer[100];

	while (!CRenderer::GetRenderer().ShouldClose())
	{
		time_from_start = clock();
		if (time_from_start % 1000 == 0)
		{
			CRenderer::GetRenderer().Tick();
			sprintf(buffer, "Working properly for %d", time_from_start);
			LOG_INFO(buffer);
		}
	}
}

