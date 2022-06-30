#pragma once
#include <Engine/Components/Core.h>
#include "../../Physics/Filters.h"

namespace Game
{
	// Doesn't need an actual updating
	class HealthComponent : public Engine::IComponent
	{
	public:
		HealthComponent(Engine::GameObject& obj, Engine::GameObjectTag collisionTagMask);
		~HealthComponent() override = default;

		void SetHealth(int health);
		void ApplyDamage(int amount);

		int GetHealth() const;
		int GetMaxHealth() const;
	
		void OnCollisionStart(Engine::GameObject* other) override;

	private:
		int m_maxHealth = 5;
		int m_currentHealth = 5;
		Engine::GameObjectTag m_collisionTagMask;
	};

}