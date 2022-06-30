#include "HealthComponent.h"

namespace Game
{
	HealthComponent::HealthComponent(Engine::GameObject& obj, Engine::GameObjectTag collisionTagMask)
		: IComponent(obj)
		, m_collisionTagMask(collisionTagMask)
	{

	}

	void HealthComponent::SetHealth(int health)
	{
		m_currentHealth = health;
		m_maxHealth = (health > m_maxHealth) ? health : m_maxHealth;
	}

	int HealthComponent::GetHealth() const
	{
		return m_currentHealth;
	}

	int HealthComponent::GetMaxHealth() const
	{
		return m_maxHealth;
	}

	void HealthComponent::OnCollisionStart(Engine::GameObject* other)
	{
		if (Engine::HasGameObjectTagFlag(m_collisionTagMask, other->Tag))
			ApplyDamage(5);
	}

	void HealthComponent::ApplyDamage(int amount)
	{
		m_currentHealth -= amount;

		if (m_currentHealth <= 0)
		{
			// signal + destroy
			// maybe call "Die" function/state?
			Owner.Destroy();
		}
	}

}