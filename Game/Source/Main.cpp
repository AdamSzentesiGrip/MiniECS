#include <iostream>
#include <type_traits>

#include "Engine.h"
#include "Components/EngineComponent.h"
#include "Components/GameComponent.h"
#include "Components/StupidComponent.h"
#include "Systems/EngineSystem.h"
#include "Systems/GameSystem.h"

int main()
{
	LOG("");
	LOG("~ MINI GAME RUNNING ~");
	LOG("");

	// ENGINE

	Mini::Engine engine;

	// SYSTEMS

	engine.AddSystem<Mini::EngineSystem>();
	engine.AddSystem<GameSystem>();

	// ENTITIES

	int_entityID entity0 = engine.CreateEntity();
	int_entityID entity1 = engine.CreateEntity("Funny name");
	int_entityID entity2 = engine.CreateEntity("Very poor name");

	// COMPONENTS

	Mini::EngineComponent ec0;
	StupidComponent sc0;
	GameComponent gc0;

	ec0.FloatValue = 456.123f;
	engine.AddComponent(entity0, ec0);
	sc0.CharValue = 4;
	engine.AddComponent(entity0, sc0);
	gc0.IntValue = 6;
	engine.AddComponent(entity0, gc0);

	gc0.IntValue = 321;
	engine.AddComponent(entity1, gc0);
	sc0.CharValue = 2;
	engine.AddComponent(entity1, sc0);

	sc0.CharValue = 50;
	engine.AddComponent(entity2, sc0);

	// DEBUG

	LOG("RESULT e1: " << (int)engine.GetComponent<StupidComponent>(entity1)->CharValue);
	LOG("RESULT e2: " << (int)engine.GetComponent<StupidComponent>(entity2)->CharValue);

	engine.DebugEntity(entity0);
	engine.DebugEntity(entity1);
	engine.DebugEntity(entity2);

	// UPDATE

	engine.UpdateSystems();

	engine.UpdateSystems();

	GameComponent gc1;
	gc1.IntValue = 987;
	engine.AddComponent(entity1, gc1);

	engine.UpdateSystems();

	engine.RemoveComponent<GameComponent>(entity0);
	engine.RemoveComponent<StupidComponent>(entity0);

	engine.UpdateSystems();

	// DEBUG

	engine.DebugEntity(entity0);

	LOG("RESULT e1: " << (int)engine.GetComponent<StupidComponent>(entity1)->CharValue);
	LOG("RESULT e2: " << (int)engine.GetComponent<StupidComponent>(entity2)->CharValue);

	char c;
	std::cin >> c;

	return 0;
}