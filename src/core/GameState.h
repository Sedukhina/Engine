#pragma once

#include "Player.h"
#include "Level.h"

// Class which contains and can give information about current state of game: active player, level, etc 
class CGameState
{
public:
	CGameState() {};
	~CGameState() {};

	void Initialize(CLevel Level);

	SPlayer* GetPlayer() { return CurrentPlayer.get(); };

private:
	std::shared_ptr<SPlayer> CurrentPlayer;
	std::shared_ptr<CLevel> CurrentLevel;
};


