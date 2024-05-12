#include "GetGameGlobals.h"
#include "GameState.h"
#include "AssetManager/AssetManager.h"

SPlayer* GetPlayer()
{
	return GetGameState().GetPlayer();
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