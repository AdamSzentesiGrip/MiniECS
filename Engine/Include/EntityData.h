#pragma once

#include <bitset>
#include <vector>

#include "Common.h"

namespace Mini
{
	class EntityData
	{
	public:
		const char* Name;
		int_entityID EntityID;
		componentKey EntityComponentKey;
		size_t ComponentIndices[GetMaxComponentID()];

		EntityData(int_entityID entityID, const char* name)
		{
			Init(entityID, name);
		}

		void Init(int_entityID entityID, const char* name)
		{
			Name = name;
			EntityID = entityID;
			EntityComponentKey = 0;
		}
	};
}
