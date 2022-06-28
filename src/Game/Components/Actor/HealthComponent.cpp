#include "HealthComponent.h"

namespace Game
{
	HealthComponent::HealthComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{

	}

	void HealthComponent::SetHealth(int health)
	{
		m_currentHealth = health;
		m_maxHealth = (health > m_maxHealth) : health ? m_maxHealth;
	}

	int HealthComponent::GetHealth() const
	{
		return m_currentHealth;
	}

	int HealthComponent::GetMaxHealth() const
	{
		return m_maxHealth;
	}

}