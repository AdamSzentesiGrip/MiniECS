#pragma once

#include <vector>

#include "Common.h"
#include "EntityData.h"

namespace Mini
{
	class API EntityManager
	{
	private:
		std::vector<EntityData*>* _EntityData;
		std::vector<int_entityID>* _AvailableEntityIndices;
		int_entityID _NextEntityID = 0;

	public:
		EntityManager();
		~EntityManager();

		int_entityID CreateEntity(size_t systemCount, const char* name);
		void DestroyEntity(int_entityID entityID);
		EntityData* GetEntityData(int_entityID entityID);
		
	};
}
