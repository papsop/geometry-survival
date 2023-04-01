#include "RPGComponent.h"
#include "../../Core/RPG/Buff.h"
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
		SetStatBase(RPGStats::AMMO_HITS, rpgActorDef.AmmoHits);
		SetStatBase(RPGStats::PICKUP_FIELD_SIZE, rpgActorDef.PickUpFieldSize);
		SetStatBase(RPGStats::BURNING_DAMAGE, rpgActorDef.BurningDamage);

		SetStatBase(RPGStats::AMMO_ON_KILL, 0);

		ResetModifiers();
	}

	void RPGComponent::OnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	void RPGComponent::VirtualOnActivated()
	{
		IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void RPGComponent::VirtualOnDeactivated()
	{
		IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

	RPGComponent::~RPGComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void RPGComponent::Update(float dt)
	{
		ResetModifiers();
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
		buff->SetOwnerRPGComponent(this);

		if (buff->GetBuffTag() == Buff::BuffTag::None)
		{
			m_buffs.push_back(std::move(buff));
		}
		else
		{ // If there is a special BuffTag - overwrite already existing buff instead of adding it
			auto newEnd = std::remove_if(m_buffs.begin(), m_buffs.end(),
				[&](const ptr_Buff& b)
				{
					return b->GetBuffTag() == buff->GetBuffTag();
				}
			);
			m_buffs.erase(newEnd, m_buffs.end());
			m_buffs.push_back(std::move(buff));
		}
	}

	void RPGComponent::ResetModifiers()
	{
		for (auto&& bonus : m_additiveStatBonus) bonus = 0.0f;
		for (auto&& bonus : m_percentageStatBonus) bonus = 1.0f;
	}

  void RPGComponent::Debug(Engine::view::IViewStrategy* viewStrategy)
  {
    // Active buffs
    Engine::math::Vec2 pos = Owner.GetTransform()->GetPosition() + Engine::math::Vec2(0.0f, -2.0f);
		std::string val{};

		for (const auto& b : m_buffs)
		{
			auto* buff = b.get();
			val += std::to_string(static_cast<int>(buff->GetBuffTag())) + "\n";
		}

    viewStrategy->DebugRenderText(Engine::ITransform::PositionSpace::WorldSpace, val, pos, true, 12.0f, sf::Color::Yellow);
  }

	float RPGComponent::GetStat(RPGStats stat)
	{
		if (stat == RPGStats::COUNT)
		{
			LOG_WARN("Trying to retrieve RPGStats::Count, returning 0.0f");
			return 0.0f;
		}

		size_t statIndex = static_cast<size_t>(stat);
		float resultValue = (m_statBase[statIndex] * m_percentageStatBonus[statIndex]) + m_additiveStatBonus[statIndex];
		return (resultValue < 0.0f) ? 0.0f : resultValue;
	}

	void RPGComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);
	}

}