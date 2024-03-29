#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include "../Actor/ActorComponent.h"
#include "../Actor/RPGComponent.h"

namespace Game
{
	class PlayerComponent : public Engine::IComponent
	{
	public:
		PlayerComponent(Engine::GameObject& obj);
		~PlayerComponent() override = default;

		void VirtualOnCreate() override;
		void OnDestroy() override;

		void OnCollisionStart(Engine::CollisionData& collision) override;

		void OnDeath();
	protected:
		void VirtualOnActivated() override;
		void VirtualOnDeactivated() override;

	private:
		ActorComponent* m_actorComponent = nullptr;
		RPGComponent* m_rpgComponent = nullptr;
	};
};