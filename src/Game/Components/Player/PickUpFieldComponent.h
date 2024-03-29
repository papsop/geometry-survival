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

		void VirtualOnCreate() override;
		void OnDestroy() override;
		void Update(float dt) override;

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;
	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	private:
		b2Fixture* m_fixture;
		b2Shape* m_fixtureShape;
	};
}