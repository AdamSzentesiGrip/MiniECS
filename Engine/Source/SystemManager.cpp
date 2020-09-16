#include "../Include/SystemManager.h"

namespace Mini
{
	SystemManager::SystemManager()
	{
		_Systems = new std::vector<SystemBase*>();
	}

	SystemManager::~SystemManager()
	{
		delete _Systems;
	}

	void SystemManager::AddSystemInternal(ComponentManager* componentManager, SystemBase* system, const char* name)
	{
		LOG("ADD + SYSTEM TO CUEUE POSITION " << _Systems->size() << ": " << name);

		system->_Name = name;
		_Systems->push_back(system);
		system->InitBase(componentManager);
	}

	void SystemManager::UpdateSystems()
	{
		for (SystemBase* system : *_Systems)
		{
			system->UpdateBase();
		}
	}

	size_t SystemManager::GetSystemCount()
	{
		return _Systems->size();
	}

}