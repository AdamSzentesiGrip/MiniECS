#include "../Include/Engine.h"

namespace Mini
{
	Engine::Engine()
	{
		_SystemManager = new SystemManager();
		_EntityManager = new EntityManager();
		_ComponentManager = new ComponentManager();
	}

	Engine::~Engine()
	{
		delete _SystemManager;
		delete _EntityManager;
		delete _ComponentManager;
	}

	void Engine::UpdateSystems()
	{
		LOG("");
		LOG("UPDATE:");
		_SystemManager->UpdateSystems();
	}

	int_entityID Engine::CreateEntity(const char* name)
	{
		return _EntityManager->CreateEntity(_SystemManager->GetSystemCount(), name);
	}

	// DEBUG

	bool Engine::HasComponent(int_entityID entityID, int_componentID componentID)
	{
		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		return _ComponentManager->HasComponent(entityData, componentID);
	}

	void Engine::DebugEntity(int_entityID entityID)
	{
		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		LOG("");
		LOG("DEBUG ENTITY: " << entityData->Name);

		// This is weird but helps to iterate any valid int (ie. uint8 has GetMaxComponentID() = 256, for loop would fail to infinite loop on 255)
		int_componentID componentID = 0;
		do
		{
			if (HasComponent(entityID, componentID))
			{
				//ComponentBase* component = _ComponentManager->GetComponentFromID(entityData, componentID);
				LOG(" - COMPONENT: " << _ComponentManager->GetComponentTypeName(componentID) << " ON INDEX " << entityData->ComponentIndices[componentID]);
			}

			componentID++;
		} while (componentID > 0 && componentID < GetMaxComponentID());
	}

}