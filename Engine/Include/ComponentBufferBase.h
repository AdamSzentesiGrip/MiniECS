#pragma once

#include "Common.h"
#include "ComponentBase.h"

namespace Mini
{
	class ComponentBufferBase
	{
	public:
		virtual size_t AddComponent(ComponentBase& component) = 0;
		virtual ComponentBase* GetComponent(size_t index) = 0;
		virtual int_entityID RemoveComponent(size_t index) = 0;
		virtual void UpdateComponent(size_t index, ComponentBase& component) = 0;
		virtual const size_t GetComponentHashCode() = 0;
		virtual const char* GetComponentName() = 0;
		virtual const size_t GetComponentSize() = 0;
		virtual const int_componentID GetComponentID() = 0;

	};
}