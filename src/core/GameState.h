#pragma once

#include "Player.h"
#include "Level.h"

// Class which contains and can give information about current state of game: active player, level, etc 
class CGameState
{
public:
	CGameState() {};
	~CGameState() {};

	__declspec(dllexport) void Initialize(CLevel Level);

	__declspec(dllexport) SPlayer* GetPlayer() { return CurrentPlayer.get(); };
	__declspec(dllexport) CLevel* GetLevel() { return CurrentLevel.get(); };

private:
	std::shared_ptr<SPlayer> CurrentPlayer;
	std::shared_ptr<CLevel> CurrentLevel;
};


