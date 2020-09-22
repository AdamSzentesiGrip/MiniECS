#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"

namespace Mini
{
	class API SystemBase
	{
		friend class SystemManager;

	private:
		ComponentManager* _ComponentManager;
		EntityManager* _EntityManager;
		componentKey* _ComponentKey;
		const char* _Name;

	public:
		SystemBase();
		void InitBase(ComponentManager* componentManager, EntityManager* entityManager);
		void UpdateBase();

	protected:
		virtual void Init() = 0;
		virtual void RegisterDefaultComponentType() = 0;
		bool IsEntityCompliant(ComponentBase& component);
		virtual void Process(ComponentManager* componentManager) = 0;
		const char* GetName();

		template<typename ComponentType> int_componentID RegisterComponentType()
		{
			int_componentID componentID = _ComponentManager->RegisterComponentType<ComponentType>();
			RegisterComponentTypeInternal(componentID);
			
			return componentID;
		}

		template<typename ComponentType>
		ComponentType* GetComponent(int_entityID entityID, int_componentID compoentID)
		{
			EntityData* entityData = _EntityManager->GetEntityData(entityID);
			return (ComponentType*)_ComponentManager->GetComponent(entityData, compoentID);
		}

	private:
		void RegisterComponentTypeInternal(int_componentID componentID);
	};
}
