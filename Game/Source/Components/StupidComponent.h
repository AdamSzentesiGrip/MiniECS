#pragma once

#include "Component.h"

struct StupidComponent : public Mini::Component<StupidComponent>
{
	char CharValue;
};

