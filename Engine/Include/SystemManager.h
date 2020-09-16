#pragma once

#include <vector>

#include "System.h"
#include "ComponentManager.h"

namespace Mini
{
	class SystemManager
	{
	private:
		std::vector<SystemBase*>* _Systems;

	public:
		SystemManager();
		~SystemManager();
		void UpdateSystems();
		size_t GetSystemCount();

		template<typename SystemType>
		void AddSystem(ComponentManager* componentManager)
		{
			static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemManager.AddSystem<SystemType> SystemType must be a Mini::System derivative");
			AddSystemInternal(componentManager, new SystemType(), typeid(SystemType).name());
		}

	private:
		void API AddSystemInternal(ComponentManager* componentManager, SystemBase* system, const char* name);
	};
}