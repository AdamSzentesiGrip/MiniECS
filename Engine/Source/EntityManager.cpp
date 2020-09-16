#include "../Include/EntityManager.h"

namespace Mini
{
	EntityManager::EntityManager()
	{
		_EntityData = new std::vector<EntityData*>();
	}

	EntityManager::~EntityManager()
	{
		delete _EntityData;
	}

	int_entityID EntityManager::CreateEntity(size_t systemCount, const char* name)
	{
		int_entityID entityID = _NextEntityID;
		
		_EntityData->push_back(new EntityData(entityID, name));
		_NextEntityID++;
		
		LOG("NEW ENTITIY " << entityID << ": " << name);
		return entityID;
	}

	EntityData* EntityManager::GetEntityData(int_entityID entityID)
	{
		return _EntityData->at(entityID);
	}

}
