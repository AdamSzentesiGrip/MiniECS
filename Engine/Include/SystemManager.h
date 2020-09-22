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
		void AddSystem(ComponentManager* componentManager, EntityManager* entityManager)
		{
			const char* name = typeid(SystemType).name();
			SystemBase* system = new SystemType();

			LOG("ADD + SYSTEM TO CUEUE POSITION " << _Systems->size() << ": " << name);

			system->_Name = name;
			_Systems->push_back(system);
			system->InitBase(componentManager, entityManager);
		}

	//private:
	//	void API AddSystemInternal(ComponentManager* componentManager, SystemBase* system, const char* name);
	};
}