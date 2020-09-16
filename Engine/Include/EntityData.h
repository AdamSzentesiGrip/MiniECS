#pragma once

#include <bitset>
#include <vector>

#include "Common.h"

namespace Mini
{
	class EntityData
	{
	public:
		EntityData(int_entityID entityID, const char* name)
		{
			Name = name;
			EntityID = entityID;
			EntityComponentKey = 0;
		}

		const char* Name;
		componentKey EntityComponentKey;
		int_entityID EntityID;
		size_t ComponentIndices[GetMaxComponentID()];
	};
}
