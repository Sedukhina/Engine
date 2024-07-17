#include "GameState.h"

void CGameState::Initialize(CLevel Level)
{
	CurrentLevel = std::make_shared<CLevel>(Level);
	//TODO: Get start values from level 
	//SCamera Camera(glm::vec3(500), glm::normalize(glm::vec3(-10)));
	SCamera Camera(glm::vec3(0, 200, 1000), glm::normalize(glm::vec3(0, 0, -10)));
	CurrentPlayer =  std::make_shared<SPlayer>(SPlayer(glm::vec3(3.f), glm::normalize(glm::vec3(-1.f)), Camera));
}
