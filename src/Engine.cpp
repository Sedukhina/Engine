#include "Engine.h"
#include <time.h>
#include <cstdio>
#include "render/Renderer.h"
#include "GameState.h"
#include "Level.h"
#include "AssetManager/AssetManager.h"

bool Engine::StartUp()
{
	auto Controller = GetInputController();
	LOG_INFO("Input Controller Initialized");
	if (!CRenderer::GetRenderer().StartUp())
	{
		return 0;
	}
	LOG_INFO("Engine succesfully started up");
	CLevel Level = CLevel();
	GetGameState().Initialize(Level);
	auto Model = GetAssetManager().ImportModel("/Test_models/metal-shelf-14mb/source/metal shelf.fbx");
	//auto ID = GetAssetManager().ImportModel("/Test_models/castle-of-loarre/source/Loarre/Loarre.fbx");
	//auto Model = GetAssetManager().ImportModel("/Test_models/chinese-pagoda/source/BaotaS/BaotaS.obj");

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
		Tick();
	}
}

void Engine::Tick()
{
	clock_t time_from_start = clock();
	if (time_from_start % 1000 == 0)
	{
		char buffer[100];
		CRenderer::GetRenderer().Tick();
		sprintf(buffer, "Working properly for %d", time_from_start);
		LOG_INFO(buffer);
	}
}