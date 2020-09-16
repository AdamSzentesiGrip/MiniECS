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
		void DestroyEntity(int_entityID entityID);
		void ApplyOnAllComponents(int_entityID entityID, void (Engine::* func) (int_entityID, int_componentID));

		// COMPONENTS

		template<typename ComponentType> void RegisterComponentType()
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::RegisterComponentType<ComponentType> ComponentType must be a Mini::Component derivative");

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
			RemoveComponent(entityID, componentID);
		}

		// SYSTEMS

		void UpdateSystems();

		template<typename SystemType> void AddSystem()
		{
			static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemManager.AddSystem<SystemType> SystemType must be a Mini::System derivative");

			_SystemManager->AddSystem<SystemType>(_ComponentManager);
		}

		// DEBUG

		void DebugEntity(int_entityID entityID);

	private:
		void RemoveComponent(int_entityID entityID, int_componentID componentID);

		// TODO: Create rtti with contiguous type indexing

		template<typename ComponentType>
		int_componentID GetComponentID(size_t componentHashCode)
		{
			size_t hashCode = typeid(ComponentType).hash_code();
		}

		// DEBUG

		bool HasComponent(int_entityID entityID, int_componentID componentID);
		void DebugComponent(int_entityID entityID, int_componentID componentID);
	};
}