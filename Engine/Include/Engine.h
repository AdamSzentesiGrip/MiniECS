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

	public:
		int_entityID CreateEntity(const char* name = "");
		void DestroyEntity(int_entityID entityID);

		// COMPONENTS

	public:
		template<typename ComponentType> void RegisterComponentType()
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::RegisterComponentType<ComponentType> ComponentType must be a Mini::Component derivative");

			_ComponentManager->RegisterComponentType<ComponentType>();
		}

		template<typename ComponentType> void AddComponent(int_entityID entityID, ComponentType& component)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::AddComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			int_componentID componentID = GetComponentID<ComponentType>();

			_ComponentManager->AddComponent(entityData, component, componentID);
		}

		template<typename ComponentType> ComponentType* GetComponent(int_entityID entityID)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::GetComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			int_componentID componentID = GetComponentID<ComponentType>();

			return (ComponentType*)_ComponentManager->GetComponent(entityData, componentID);
		}

		template<typename ComponentType> void RemoveComponent(int_entityID entityID)
		{
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value, "Engine::RemoveComponent<ComponentType> ComponentType must be a Mini::Component derivative");

			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			int_componentID componentID = GetComponentID<ComponentType>();

			RemoveComponent(entityData, componentID);
		}

	private:
		void RemoveComponent(EntityData* entityData, int_componentID componentID);
		void ApplyOnAllComponents(EntityData* entityData, void (Engine::* func) (EntityData*, int_componentID));

		// TODO: Create rtti with contiguous type indexing
		template<typename ComponentType> int_componentID GetComponentID()
		{
			size_t componentHashCode = typeid(ComponentType).hash_code();
			return _ComponentManager->GetComponentID(componentHashCode);
		}

		// SYSTEMS

	public:
		void UpdateSystems();

		template<typename SystemType> void AddSystem()
		{
			static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemManager.AddSystem<SystemType> SystemType must be a Mini::System derivative");

			_SystemManager->AddSystem<SystemType>(_ComponentManager);
		}

		// DEBUG

	public:
		void DebugEntity(int_entityID entityID);

	private:
		void DebugComponent(EntityData* entityData, int_componentID componentID);

	};
}