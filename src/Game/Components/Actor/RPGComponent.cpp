#include "RPGComponent.h"
#include <Engine/Debug/Logger.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
	RPGComponent::RPGComponent(Engine::GameObject& obj, const RPGActorDef& rpgActorDef)
		: IComponent(obj)
		, m_statBase()
		, m_statBuffBonus()
	{
		SetStatBase(RPGStats::MAX_HEALTH, rpgActorDef.MaxHealth);
		SetStatBase(RPGStats::CURRENT_HEALTH, rpgActorDef.MaxHealth);
		SetStatBase(RPGStats::MOVEMENT_SPEED, rpgActorDef.MovementSpeed);
		SetStatBase(RPGStats::ATTACK_SPEED, rpgActorDef.AttackSpeed);
		SetStatBase(RPGStats::WEAPON_DAMAGE, rpgActorDef.WeaponDamage);
		SetStatBase(RPGStats::AMMO_BONUS, rpgActorDef.AmmoBonus);
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
		for (auto&& bonus : m_statBuffBonus) bonus = 0;

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
				buff->IterateOverModifiers(
					[&](const BuffModifierEntry& modifier)
					{
						m_statBuffBonus[static_cast<size_t>(modifier.Stat)] += modifier.ValueModifier;
					}
				);
				// move loop
				it++;
			}
		}

		if (GetStat(RPGStats::CURRENT_HEALTH) <= 0.0f)
		{
			Owner.SendMessageTo(&Owner, Engine::MessageType::MSG_DIED);
			Owner.Destroy();
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
		// If there is a special BuffTag - overwrite already existing buff instead of adding it
		if (buff->GetBuffTag() == Buff::BuffTag::None)
		{
			m_buffs.push_back(std::move(buff));
		}
		else
		{
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

		auto statIndex = static_cast<size_t>(stat);

		return m_statBase[statIndex] + m_statBuffBonus[statIndex];
	}



}