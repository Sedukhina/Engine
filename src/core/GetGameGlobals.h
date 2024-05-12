#pragma once
#include <memory>

class CGameState;
class SPlayer;
class SCamera;
class CAssetManager;

extern SPlayer* GetPlayer();

extern CGameState& GetGameState();

extern CAssetManager& GetAssetManager();