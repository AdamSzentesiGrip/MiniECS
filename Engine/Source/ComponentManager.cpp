#include "../Include/ComponentManager.h"

namespace Mini
{
	ComponentManager::ComponentManager()
	{
		_ComponentIDRegister = new std::map<size_t, int_componentID>();
		_ComponentBuffers = new std::vector<ComponentBufferBase*>();
	}

	ComponentManager::~ComponentManager()
	{
		delete _ComponentIDRegister;
		delete _ComponentBuffers;
	}

	bool ComponentManager::IsRegistered(size_t hashCode)
	{
		return (_ComponentIDRegister->count(hashCode) > 0);
	}

	void ComponentManager::RegisterComponentType(ComponentBufferBase* componentBuffer)
	{
		int_componentID componentID = componentBuffer->GetComponentID();
		size_t componentHashCode = componentBuffer->GetComponentHashCode();
		const char* componentName = componentBuffer->GetComponentName();

		LOG("REG COMPONENT " << static_cast<uint32_t>(componentID) << ": " << componentName);

		_ComponentIDRegister->insert({ componentHashCode, componentID });
		_ComponentBuffers->push_back(componentBuffer);

		return;
	}

	void ComponentManager::AddComponent(EntityData* entityData, ComponentBase& component, int_componentID componentID)
	{
		component._EntityData = entityData;

		if (AddComponentKey(entityData, componentID))
		{
			LOG("ADD COMPONENT TO ENTITY " << (int)entityData->EntityID << ": " << GetComponentTypeName(componentID));

			entityData->ComponentIndices[componentID] = (*_ComponentBuffers)[componentID]->AddComponent(component);
		}
		else
		{
			LOG("UPD COMPONENT ON ENTITY " << (int)entityData->EntityID << ": " << GetComponentTypeName(componentID));

			(*_ComponentBuffers)[componentID]->UpdateComponent(entityData->ComponentIndices[componentID], component);
		}
	}

	ComponentBase* ComponentManager::GetComponent(EntityData* entityData, int_componentID componentID)
	{
		if (!HasComponent(entityData, componentID)) return nullptr;

		LOG("GET COMPONENT FROM ENTITY " << (int)entityData->EntityID << ": " << GetComponentTypeName(componentID));

		return (*_ComponentBuffers)[componentID]->GetComponent(entityData->ComponentIndices[componentID]);
	}

	int_entityID ComponentManager::RemoveComponent(size_t index, int_componentID componentID)
	{
		LOG("REM COMPONENT FROM ENTITY " << (int)index << ": " << GetComponentTypeName(componentID));

		return (*_ComponentBuffers)[componentID]->RemoveComponent(index);
	}

	int_componentID ComponentManager::GetComponentID(size_t componentHashCode)
	{
		return _ComponentIDRegister->at(componentHashCode);
	}

	componentKey ComponentManager::GetComponentKey(int_componentID componentID)
	{
		componentKey componentKey = 1;
		componentKey <<= componentID;
		return componentKey;
	}

	bool ComponentManager::HasComponentKey(EntityData* entityData, componentKey componentKey)
	{
		return ((entityData->EntityComponentKey & componentKey) != 0);
	}

	bool ComponentManager::HasComponent(EntityData* entityData, int_componentID componentID)
	{
		return HasComponentKey(entityData, GetComponentKey(componentID));
	}

	bool ComponentManager::AddComponentKey(EntityData* entityData, int_componentID componentID)
	{
		componentKey componentKey = GetComponentKey(componentID);

		if(HasComponentKey(entityData, componentKey))
		{
			return false;
		}

		entityData->EntityComponentKey |= componentKey;

		return true;
	}

	bool ComponentManager::RemoveComponentKey(EntityData* entityData, int_componentID componentID)
	{
		componentKey componentKey = GetComponentKey(componentID);

		if (!HasComponentKey(entityData, componentKey))
		{
			return false;
		}

		entityData->EntityComponentKey &= ~componentKey;

		return true;
	}

	const char* ComponentManager:: GetComponentTypeName(int_componentID componentID)
	{
		return (*_ComponentBuffers)[componentID]->GetComponentName();
	}

}