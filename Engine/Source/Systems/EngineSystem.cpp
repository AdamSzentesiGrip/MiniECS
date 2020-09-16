#include "../../Include/Systems/EngineSystem.h"

namespace Mini
{
	void EngineSystem::Init()
	{
	}

	void EngineSystem::Process(EngineComponent& component)
	{
		LOG("  - float value: " << component.FloatValue);
		
	}


}