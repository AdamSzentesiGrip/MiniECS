#include "../Include/SystemBase.h"

namespace Mini
{
	SystemBase::SystemBase()
	{
		_ComponentKey = new componentKey();
	}

	void SystemBase::InitBase(ComponentManager* componentManager)
	{
		_ComponentManager = componentManager;
		RegisterDefaultComponentType();
		Init();
	}

	void SystemBase::UpdateBase()
	{
		LOG(" PROCESS: " << GetName());

		Process(_ComponentManager);
	}

	void SystemBase::RegisterComponentTypeInternal(int_componentID componentID)
	{
		*_ComponentKey |= _ComponentManager->GetComponentKey(componentID);
	}

	const char* SystemBase::GetName()
	{
		return _Name;
	}
}