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

	// ENTITIES

	int_entityID Engine::CreateEntity(const char* name)
	{
		return _EntityManager->CreateEntity(name);
	}

	void Engine::DestroyEntity(int_entityID entityID)
	{
		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		ApplyOnAllComponents(entityData, &Engine::RemoveComponent);
		_EntityManager->DestroyEntity(entityID);
	}

	// COMPONENTS

	void Engine::RemoveComponent(EntityData* entityData, int_componentID componentID)
	{
		if (!_ComponentManager->RemoveComponentKey(entityData, componentID)) return;

		size_t index = entityData->ComponentIndices[componentID];
		int_entityID movedComponentEntityID = _ComponentManager->RemoveComponent(index, componentID);
		EntityData* movedComponentEntityData = _EntityManager->GetEntityData(movedComponentEntityID);
		movedComponentEntityData->ComponentIndices[componentID] = index;
	}

	void Engine::ApplyOnAllComponents(EntityData* entityData, void (Engine::* func) (EntityData*, int_componentID))
	{
		// This is weird but helps to iterate any valid int (ie. uint8 has GetMaxComponentID() = 256, for loop would fail to infinite loop on 255)
		int_componentID componentID = 0;
		do
		{
			(this->*func)(entityData, componentID);
			componentID++;
		} while (componentID > 0 && componentID < GetMaxComponentID());
	}

	// SYSTEMS

	void Engine::UpdateSystems()
	{
		LOG("");
		LOG("UPDATE:");
		_SystemManager->UpdateSystems();
	}

	// DEBUG

	void Engine::DebugEntity(int_entityID entityID)
	{
		LOG("");
		LOG("DEBUG ENTITY: " << _EntityManager->GetEntityData(entityID)->Name);

		EntityData* entityData = _EntityManager->GetEntityData(entityID);

		ApplyOnAllComponents(entityData, &Engine::DebugComponent);
	}

	void Engine::DebugComponent(EntityData* entityData, int_componentID componentID)
	{
		if (!_ComponentManager->HasComponent(entityData, componentID)) return;

		LOG(" - COMPONENT: " << _ComponentManager->GetComponentTypeName(componentID) << " ON INDEX " << entityData->ComponentIndices[componentID]);
	}

}