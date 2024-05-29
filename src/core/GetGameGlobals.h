#pragma once
#include <memory>

class CGameState;
class SPlayer;
class SCamera;
class CLevel;
class CAssetManager;

extern SPlayer* GetPlayer();

extern CLevel* GetLevel();

extern CGameState& GetGameState();

extern CAssetManager& GetAssetManager();