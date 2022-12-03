#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class PlayerComponent : public Engine::IComponent
	{
	public:
		PlayerComponent(Engine::GameObject& obj);
		~PlayerComponent() override = default;

		void OnCollisionStart(Engine::CollisionData& collision) override;


		void OnDestroy() override;

	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	};
};