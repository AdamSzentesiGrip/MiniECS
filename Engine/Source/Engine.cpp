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

	// ENTITIES

	int_entityID Engine::CreateEntity(const char* name)
	{
		return _EntityManager->CreateEntity(_SystemManager->GetSystemCount(), name);
	}

	void Engine::DestroyEntity(int_entityID entityID)
	{
		ApplyOnAllComponents(entityID, &Engine::RemoveComponent);
		_EntityManager->DestroyEntity(entityID);
	}

	void Engine::ApplyOnAllComponents(int_entityID entityID, void (Engine::* func) (int_entityID, int_componentID))
	{
		// This is weird but helps to iterate any valid int (ie. uint8 has GetMaxComponentID() = 256, for loop would fail to infinite loop on 255)
		int_componentID componentID = 0;
		do
		{
			(this->*func)(entityID, componentID);
			componentID++;
		} while (componentID > 0 && componentID < GetMaxComponentID());
	}

	void Engine::RemoveComponent(int_entityID entityID, int_componentID componentID)
	{
		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		if (!_ComponentManager->RemoveComponentKey(entityData, componentID)) return;

		size_t index = entityData->ComponentIndices[componentID];
		int_entityID movedComponentEntityID = _ComponentManager->RemoveComponent(index, componentID);
		EntityData* movedComponentEntityData = _EntityManager->GetEntityData(movedComponentEntityID);
		movedComponentEntityData->ComponentIndices[componentID] = index;
	}

	// DEBUG

	bool Engine::HasComponent(int_entityID entityID, int_componentID componentID)
	{
		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		return _ComponentManager->HasComponent(entityData, componentID);
	}

	void Engine::DebugEntity(int_entityID entityID)
	{
		LOG("");
		LOG("DEBUG ENTITY: " << _EntityManager->GetEntityData(entityID)->Name);

		ApplyOnAllComponents(entityID, &Engine::DebugComponent);
	}

	void Engine::DebugComponent(int_entityID entityID, int_componentID componentID)
	{
		if (!HasComponent(entityID, componentID)) return;

		EntityData* entityData = _EntityManager->GetEntityData(entityID);
		LOG(" - COMPONENT: " << _ComponentManager->GetComponentTypeName(componentID) << " ON INDEX " << entityData->ComponentIndices[componentID]);
	}

}