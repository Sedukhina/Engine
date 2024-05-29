#include "Engine.h"
#include <cstdio>
#include "render/Renderer.h"
#include "GameState.h"
#include "Level.h"
#include "AssetManager/AssetManager.h"

bool Engine::StartUp()
{
	LastFrame = clock();
	auto Controller = GetInputController();
	LOG_INFO("Input Controller Initialized");
	if (!CRenderer::GetRenderer().StartUp())
	{
		return 0;
	}
	CLevel Level = CLevel();
	GetGameState().Initialize(Level);
	LOG_INFO("Engine succesfully started up");
	return 1;
}

void Engine::ShutDown()
{
	CRenderer::GetRenderer().ShutDown();
	LOG_INFO("Engine succesfully shutted down");
}

void Engine::Mainloop()
{
	while (!CRenderer::GetRenderer().ShouldClose())
	{
		clock_t DeltaTime = clock() - LastFrame + 1;
		LastFrame = clock();
		Tick(DeltaTime);
	}
}

void Engine::Tick(float DeltaTime)
{
	char buffer[100];
	CRenderer::GetRenderer().Tick(DeltaTime);
	sprintf(buffer, "FPS: %f", 1000.f/DeltaTime);
	LOG_INFO(buffer);
}