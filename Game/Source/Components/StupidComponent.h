#pragma once

#include "Component.h"

struct StupidComponent : public Mini::Component<StupidComponent>
{
	char CharValue;

protected:
	virtual void DebugComponentImpl() override
	{
		LOG((int)CharValue);
	}
};

