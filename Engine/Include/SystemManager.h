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
			AddSystemInternal(componentManager, new SystemType(), typeid(SystemType).name());
		}

	private:
		void API AddSystemInternal(ComponentManager* componentManager, SystemBase* system, const char* name);
	};
}