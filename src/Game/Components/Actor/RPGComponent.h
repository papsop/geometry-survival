#pragma once
#include "../../Core/RPG/RPGStats.h"
#include "../../Core/RPG/Buff.h"
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <memory>
#include <vector>
#include <array>

namespace Game
{
	class ActorComponent;
	
	struct RPGActorDef
	{
		unsigned int MaxHealth;
		// meters per seconds
		float MovementSpeed;
		// shots per second = weapon * (attack speed/100)
		float AttackSpeed = 100.0f;
		// damage = weapon * (damage/100)
		float WeaponDamage = 100.0f;
		// ammmo = ceil(weapon * (bonus/100)) 
		float AmmoBonus = 100.0f;
	};

	class RPGComponent : public Engine::IComponent
	{
	public:
		using ptr_Buff = std::unique_ptr<Buff>;

		RPGComponent(Engine::GameObject& obj, const RPGActorDef& rpgActorDef);
		~RPGComponent();

		void VirtualOnActivated() override;

		void Update(float dt) override;

		float GetStat(RPGStats stat);
		void  SetStatBase(RPGStats stat, float value);

		void AddBuff(ptr_Buff buff);
	private:
		
		std::vector< ptr_Buff > m_buffs;

		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBase;
		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBuffBonus;
		

	friend class ActorComponent; // only ActorComponent can own a RPGActor
	};
}