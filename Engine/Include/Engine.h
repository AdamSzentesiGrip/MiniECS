#pragma once

#include "Common.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace Mini
{
	class API Engine
	{
	private:
		SystemManager* _SystemManager;
		EntityManager* _EntityManager;
		ComponentManager* _ComponentManager;

	public:
		Engine();
		~Engine();

		// ENTITIES

		int_entityID CreateEntity(const char* name = "");

		// COMPONENTS

		template<typename ComponentType> void RegisterComponentType()
		{
			_ComponentManager->RegisterComponentType<ComponentType>();
		}

		template<typename ComponentType> void AddComponent(int_entityID entityID, ComponentType& component)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::AddComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			_ComponentManager->AddComponent(entityData, component, typeid(ComponentType).hash_code());
		}

		template<typename ComponentType> ComponentType* GetComponent(int_entityID entityID)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::GetComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			return (ComponentType*)_ComponentManager->GetComponent(entityData, typeid(ComponentType).hash_code());
		}

		template<typename ComponentType> void RemoveComponent(int_entityID entityID)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::RemoveComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			int_componentID componentID = _ComponentManager->GetComponentID(typeid(ComponentType).hash_code());

			// TODO: hide in impl

			EntityData* entityData = _EntityManager->GetEntityData(entityID);

			if (!_ComponentManager->RemoveComponentKey(entityData, componentID)) return;
			
			size_t index = entityData->ComponentIndices[componentID];
			int_entityID movedComponentEntityID = _ComponentManager->RemoveComponent(index, componentID);
			EntityData* movedComponentEntityData = _EntityManager->GetEntityData(movedComponentEntityID);
			movedComponentEntityData->ComponentIndices[componentID] = index;
		}

		// SYSTEMS

		void UpdateSystems();

		template<typename ComponentType> void AddSystem()
		{
			_SystemManager->AddSystem<ComponentType>(_ComponentManager);
		}

		// DEBUG

		bool HasComponent(int_entityID entityID, int_componentID componentID);
		void DebugEntity(int_entityID entityID);
	};
}