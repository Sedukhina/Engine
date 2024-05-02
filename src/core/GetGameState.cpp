#include "GetGameState.h"
#include "GameState.h"

SPlayer* GetPlayer()
{
	return GetGameState().GetPlayer();
}

CGameState& GetGameState()
{
	static CGameState GameState;
	return GameState;
}
