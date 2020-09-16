#pragma once

#include <vector>

#include "Common.h"
#include "ComponentBufferBase.h"
#include "ComponentBase.h"

namespace Mini
{
	template<typename ComponentType>
	class ComponentBuffer : public ComponentBufferBase
	{
	private:
		std::vector<ComponentType> _Buffer = {};

	public:
		const size_t ComponentHashCode;
		const char* ComponentName;
		const size_t ComponentSize;
		const int_componentID ComponentID;

	public:
		ComponentBuffer(size_t hashCode, const char* typeName, size_t size, int_componentID componentID):
			ComponentHashCode(hashCode),
			ComponentName(typeName),
			ComponentSize(size),
			ComponentID(componentID)
		{
			//_Buffer = new std::vector<T>();
		}

		~ComponentBuffer()
		{
			//delete _Buffer;
		}

		std::vector<ComponentType>* GetComponents()
		{
			return &_Buffer;
		}

		virtual size_t AddComponent(ComponentBase& component) override
		{
			size_t index = _Buffer.size();
			_Buffer.push_back((ComponentType&)component);
			
			return index;
		}

		virtual ComponentBase* GetComponent(size_t index) override
		{
			return &_Buffer[index];
		}

		virtual int_entityID RemoveComponent(size_t index) override
		{
			_Buffer[index] = _Buffer.back();
			_Buffer.pop_back();
			return _Buffer[index].GetEntityID();
		}

		virtual void UpdateComponent(size_t index, ComponentBase& component) override
		{
			_Buffer[index] = (ComponentType&)component;
		}

		virtual const size_t GetComponentHashCode() override { return ComponentHashCode; };
		virtual const char* GetComponentName() override { return ComponentName; };
		virtual const size_t GetComponentSize() override { return ComponentSize; };
		virtual const int_componentID GetComponentID() override { return ComponentID; };
	
	};
}