#pragma once

#include "System.h"
#include "Components/EngineComponent.h"
#include "../Components/GameComponent.h"
#include "../Components/StupidComponent.h"

class GameSystem : public Mini::System<GameComponent>
{
private:
	int_componentID _EngineComponentID;
	int_componentID _StupidComponentID;

public:
	virtual void Init() override;
	virtual void Process(GameComponent& component) override;

};