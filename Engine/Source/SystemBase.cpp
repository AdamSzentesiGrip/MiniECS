#include "../Include/SystemBase.h"

namespace Mini
{
	SystemBase::SystemBase()
	{
		_ComponentKey = new componentKey();
	}

	void SystemBase::InitBase(ComponentManager* componentManager, EntityManager* entityManager)
	{
		_ComponentManager = componentManager;
		_EntityManager = entityManager;
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

	bool SystemBase::IsEntityCompliant(ComponentBase& component)
	{
		componentKey entityComponentKey = component.GetEntityComponentKey();

		return ((*_ComponentKey & entityComponentKey) == *_ComponentKey);
	}

	const char* SystemBase::GetName()
	{
		return _Name;
	}
}