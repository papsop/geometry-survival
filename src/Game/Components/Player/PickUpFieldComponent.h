#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Debug/IDebuggable.h>

#include <box2d/b2_fixture.h>

namespace Game
{
	class PickUpFieldComponent : public Engine::IComponent, public Engine::IDebuggableComponent
	{
	public:
		PickUpFieldComponent(Engine::GameObject& obj);
		~PickUpFieldComponent() override = default;

		void OnCreate() override;

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
	private:
		float m_radius;
		b2Fixture* m_fixture;
	};
}