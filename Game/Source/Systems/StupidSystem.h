#pragma once

#include "System.h"
#include "../Components/StupidComponent.h"

class StupidSystem : public Mini::System<StupidComponent>
{
public:
	virtual void Init() override;
	virtual void Process(StupidComponent& component) override;
};

