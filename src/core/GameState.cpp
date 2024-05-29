#include "GameState.h"

void CGameState::Initialize(CLevel Level)
{
	CurrentLevel = std::make_shared<CLevel>(Level);
	//TODO: Get start values from level 
	SCamera Camera(glm::vec3(300, 140, -20), glm::normalize(glm::vec3(-10, 0, 0)));
	CurrentPlayer =  std::make_shared<SPlayer>(SPlayer(glm::vec3(3.f), glm::normalize(glm::vec3(-1.f)), Camera));
}
