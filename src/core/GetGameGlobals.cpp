#include "GetGameGlobals.h"
#include "GameState.h"
#include "AssetManager/AssetManager.h"

SPlayer* GetPlayer()
{
	return GetGameState().GetPlayer();
}

CLevel* GetLevel()
{
	return GetGameState().GetLevel();
}

CGameState& GetGameState()
{
	static CGameState GameState;
	return GameState;
}

CAssetManager& GetAssetManager()
{
	static CAssetManager AssetManager;
	return AssetManager;
}