#include "GameSystem.h"

void GameSystem::Init()
{
	_EngineComponentID = RegisterComponentType<Mini::EngineComponent>();
	_StupidComponentID = RegisterComponentType<StupidComponent>();
}

void GameSystem::Process(GameComponent& component)
{
	component.IntValue++;

	component.DebugComponent();

	Mini::EngineComponent* engineComponent = GetComponent<Mini::EngineComponent>(component.GetEntityID(), _EngineComponentID);
	StupidComponent* stupidComponent = GetComponent<StupidComponent>(component.GetEntityID(), _StupidComponentID);
	
	engineComponent->DebugComponent();
	stupidComponent->DebugComponent();

}
