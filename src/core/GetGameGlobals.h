#pragma once
#include <memory>

class CGameState;
class SPlayer;
class SCamera;
class CLevel;
class CAssetManager;

__declspec(dllexport) extern SPlayer* GetPlayer();

__declspec(dllexport) extern CLevel* GetLevel();

__declspec(dllexport) extern CGameState& GetGameState();

__declspec(dllexport) extern CAssetManager& GetAssetManager();