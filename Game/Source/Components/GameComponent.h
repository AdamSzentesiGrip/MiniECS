#pragma once

#include "Component.h"

struct GameComponent : public Mini::Component<GameComponent>
{
	int IntValue;
};
