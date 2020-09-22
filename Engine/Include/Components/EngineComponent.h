#pragma once

#include "../Component.h"

namespace Mini
{
	COMPONENT(EngineComponent)
	{
		float FloatValue;

	protected:
		virtual void DebugComponentImpl() override
		{
			LOG(FloatValue);
		}
	};

}