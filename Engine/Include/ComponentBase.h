#pragma once

#include <bitset>

#include "Common.h"
#include "EntityData.h"

namespace Mini
{
	struct ComponentBase
	{
		friend class ComponentManager;
		
	private:
		// TODO: this should be direct data (copy from Entity) to speed up iteration
		EntityData* _EntityData;

	public:
		int_entityID GetEntityID() { return _EntityData->EntityID; }
		componentKey GetEntityComponentKey() { return _EntityData->EntityComponentKey; }

	};
}