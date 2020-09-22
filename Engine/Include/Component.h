#pragma once

#include "ComponentBase.h"

namespace Mini
{
	template<typename ComponentType>
	struct Component : public ComponentBase
	{
	public:
		virtual void DebugComponent() override
		{
			std::cout << "     " << typeid(ComponentType).name() << " = ";
			DebugComponentImpl();
		}

	protected:
		virtual void DebugComponentImpl() {}
	};
}
