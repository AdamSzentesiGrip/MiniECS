#pragma once

#include "../System.h"
#include "../Components/EngineComponent.h"

namespace Mini
{
	class API EngineSystem : public System<EngineComponent>
	{
	public:
		virtual void Init() override;
		virtual void Process(EngineComponent& component) override;

	};

}