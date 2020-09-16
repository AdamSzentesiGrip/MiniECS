#pragma once

#include <vector>
#include <map>

#include "Common.h"
#include "ComponentBuffer.h"
#include "Component.h"
#include "EntityData.h"

#include "../Include/Components/EngineComponent.h"

namespace Mini
{
	class API ComponentManager
	{
	private:
		std::map<size_t, int_componentID>* _ComponentIDRegister;
		std::vector<ComponentBufferBase*>* _ComponentBuffers;

	public:
		ComponentManager();
		~ComponentManager();

		template<typename ComponentType> int_componentID RegisterComponentType()
		{
			size_t componentHashCode = typeid(ComponentType).hash_code();
			const char* componentName = typeid(ComponentType).name();

			if (IsRegistered(componentHashCode))
			{
				return GetComponentID(componentHashCode);
			}

			int_componentID componentID = (int_componentID)_ComponentBuffers->size();
			size_t componentSize = sizeof(ComponentType);

			ComponentBufferBase* componentBuffer = new ComponentBuffer<ComponentType>(componentHashCode, componentName, componentSize, componentID);
			RegisterComponentType(componentBuffer);
			
			return componentID;
		}

		bool HasComponent(EntityData* entityData, int_componentID componentID);
		void AddComponent(EntityData* entityData, ComponentBase& component, int_componentID componentID);
		ComponentBase* GetComponent(EntityData* entityData, int_componentID componentID);
		int_entityID RemoveComponent(size_t index, int_componentID componentID);

		int_componentID GetComponentID(size_t componentHashCode);
		componentKey GetComponentKey(int_componentID componentID);
		bool RemoveComponentKey(EntityData* entityData, int_componentID componentID);

		template<typename ComponentType> std::vector<ComponentType>* GetComponents(int_componentID componentID)
		{
			return ((ComponentBuffer<ComponentType>*)(_ComponentBuffers->at(componentID)))->GetComponents();
		}

		// DEBUG

		const char* GetComponentTypeName(int_componentID componentID);

	private:
		bool HasComponentKey(EntityData* entityData, componentKey componentKey);
		bool IsRegistered(size_t hashCode);
		void RegisterComponentType(ComponentBufferBase* componentBuffer);
		bool AddComponentKey(EntityData* entityData, int_componentID componentID);

	};

}