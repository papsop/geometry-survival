#pragma once
#include <Engine/Components/Core.h>

namespace Game
{
	// Doesn't need an actual updating
	class HealthComponent : public Engine::IComponent
	{
	public:
		HealthComponent(Engine::GameObject& obj);
		~HealthComponent override = default;

		void SetHealth(int health);

		int GetHealth() const;
		int GetMaxHealth() const;

	private:
		int m_maxHealth;
		int m_currentHealth;
		
	};

}