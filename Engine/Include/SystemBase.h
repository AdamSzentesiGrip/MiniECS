#pragma once

#include "ComponentManager.h"

namespace Mini
{
	class API SystemBase
	{
		friend class SystemManager;

	private:
		ComponentManager* _ComponentManager;
		componentKey* _ComponentKey;
		const char* _Name;

	public:
		SystemBase();
		void InitBase(ComponentManager* componentManager);
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

	private:
		void RegisterComponentTypeInternal(int_componentID componentID);
	};
}
