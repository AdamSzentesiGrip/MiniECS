#pragma once

#include "SystemBase.h"

namespace Mini
{
	template<typename DefaultComponent>
	class System : public SystemBase
	{
	private:
		int_componentID _DefaultComponentID = 0;

	protected:
		virtual void RegisterDefaultComponentType() override
		{
			_DefaultComponentID = RegisterComponentType<DefaultComponent>();
		}

		virtual void Process(ComponentManager* componentManager) override
		{
			std::vector<DefaultComponent>* components = componentManager->GetComponents<DefaultComponent>(_DefaultComponentID);
			
			for (DefaultComponent& component : *components)
			{
				// TODO: single component type Systems should not filter Entities
				if (IsEntityCompliant(component))
				{
					LOG("  ENTITY: " << component.GetEntityID());

					Process(component);
				}
			}
		}

		virtual void Process(DefaultComponent& component) = 0;

	};
}
