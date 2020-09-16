#include "../Include/EntityManager.h"

namespace Mini
{
	EntityManager::EntityManager()
	{
		_EntityData = new std::vector<EntityData*>();
		_AvailableEntityIndices = new std::vector<int_entityID>();
	}

	EntityManager::~EntityManager()
	{
		delete _EntityData;
		delete _AvailableEntityIndices;
	}

	int_entityID EntityManager::CreateEntity(size_t systemCount, const char* name)
	{
		int_entityID entityID;

		if (_AvailableEntityIndices->size() == 0)
		{
			entityID = _NextEntityID;
			_EntityData->push_back(new EntityData(entityID, name));
			_NextEntityID++;
		}
		else
		{
			entityID = _AvailableEntityIndices->back();
			_AvailableEntityIndices->pop_back();
			(*_EntityData)[entityID]->Init(entityID, name);
		}
		
		LOG("CRE ENTITIY " << entityID << ": " << name);
		return entityID;
	}

	void EntityManager::DestroyEntity(int_entityID entityID)
	{
		LOG("DES ENTITIY " << entityID << ": " << (*_EntityData)[entityID]->Name);

		_AvailableEntityIndices->push_back(entityID);
	}

	EntityData* EntityManager::GetEntityData(int_entityID entityID)
	{
		return _EntityData->at(entityID);
	}

}
