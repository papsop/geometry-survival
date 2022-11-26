#include "RPGComponent.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
	RPGComponent::RPGComponent(Engine::GameObject& obj, const RPGActorDef& rpgActorDef)
		: IComponent(obj)
		, m_statBase()
		, m_additiveStatBonus()
		, m_percentageStatBonus()
	{
		SetStatBase(RPGStats::MAX_HEALTH, rpgActorDef.MaxHealth);
		SetStatBase(RPGStats::CURRENT_HEALTH, rpgActorDef.MaxHealth);
		SetStatBase(RPGStats::MOVEMENT_SPEED, rpgActorDef.MovementSpeed);
		SetStatBase(RPGStats::ATTACK_SPEED, rpgActorDef.AttackSpeed);
		SetStatBase(RPGStats::WEAPON_DAMAGE, rpgActorDef.WeaponDamage);
		SetStatBase(RPGStats::AMMO_BONUS, rpgActorDef.AmmoBonus);

		SetStatBase(RPGStats::AMMO_ON_KILL, 0);
	}

	void RPGComponent::VirtualOnActivated()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	RPGComponent::~RPGComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void RPGComponent::Update(float dt)
	{
		// reset all the modifiers
		for (auto&& bonus : m_additiveStatBonus) bonus = 0.0f;
		for (auto&& bonus : m_percentageStatBonus) bonus = 1.0f;

		// apply modifiers from buffs
		for (auto it = m_buffs.begin(); it != m_buffs.end(); /* */)
		{
			auto buff = it->get();
			buff->Update(dt);

			if (buff->ShouldDestroy())
			{
				it = m_buffs.erase(it);
			}
			else
			{
				// apply buff modifiers
				for (const auto& modifier : buff->GetAdditiveModifiers())
				{
					m_additiveStatBonus[static_cast<size_t>(modifier.Stat)] += modifier.ValueModifier;
				}
				for (const auto& modifier : buff->GetPercentageModifiers())
				{
					m_percentageStatBonus[static_cast<size_t>(modifier.Stat)] += modifier.ValueModifier;
				}

				// move loop
				it++;
			}
		}

		if (GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
		{
			Owner.Destroy();
		}

    if (m_additiveStatBonus[6] > 0)
    {
      LOG_WARN("RPG_Update ammoOnKill %f", m_additiveStatBonus[6]);
    }
	}

	void RPGComponent::SetStatBase(RPGStats stat, float value)
	{
		if (stat == RPGStats::COUNT)
		{
			LOG_WARN("Trying to set RPGStats::Count");
			return;
		}

		m_statBase[static_cast<size_t>(stat)] = value;
	}

	void RPGComponent::AddBuff(ptr_Buff buff)
	{
		if (buff->GetBuffTag() == Buff::BuffTag::None)
		{
			m_buffs.push_back(std::move(buff));
		}
		else
		{ // If there is a special BuffTag - overwrite already existing buff instead of adding it
			auto newEnd = std::remove_if(m_buffs.begin(), m_buffs.end(),
				[&](const ptr_Buff& buff)
				{
					return buff->GetBuffTag() == buff->GetBuffTag();
				}
			);
			m_buffs.erase(newEnd, m_buffs.end());
			m_buffs.push_back(std::move(buff));
		}
	}

	float RPGComponent::GetStat(RPGStats stat)
	{
		if (stat == RPGStats::COUNT)
		{
			LOG_WARN("Trying to retrieve RPGStats::Count, returning 0.0f");
			return 0.0f;
		}

    if (stat == RPGStats::AMMO_ON_KILL)
    {
      LOG_WARN("RPG_GetStat ammoOnKill %f", m_additiveStatBonus[static_cast<size_t>(RPGStats::AMMO_ON_KILL)]);
    }

		size_t statIndex = static_cast<size_t>(stat);
		float resultValue = (m_statBase[statIndex] * m_percentageStatBonus[statIndex]) + m_additiveStatBonus[statIndex];
		return (resultValue < 0.0f) ? 0.0f : resultValue;
	}

}