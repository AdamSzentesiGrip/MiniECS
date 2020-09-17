#include "GameSystem.h"

void GameSystem::Init()
{
	RegisterComponentType<Mini::EngineComponent>();
	RegisterComponentType<StupidComponent>();
}

void GameSystem::Process(GameComponent& component)
{
	component.IntValue++;
}
