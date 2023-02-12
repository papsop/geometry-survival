#pragma once
#include "../../Core/RPG/RPGStats.h"
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Debug/IDebuggable.h>
#include <memory>
#include <vector>
#include <array>

namespace Game
{
	class ActorComponent;
	class Buff;

	struct RPGActorDef
	{
		unsigned int MaxHealth;
		// meters per seconds
		float MovementSpeed;
		// shots per second = weapon * (attack speed/100)
		float AttackSpeed = 100.0f;
		// +weaponDamage
		float WeaponDamage = 0.0f;
		// ammmo = ceil(weapon * (bonus/100)) 
		float AmmoBonus = 100.0f;
		// how many enemies can the bullet hit (piercing)
		float AmmoHits = 1;
		// +pickupFieldSize
		float PickUpFieldSize = 10.0f;
		// burning damage, applies to bullets
		float BurningDamage = 0.0f;
	};

	class RPGComponent : public Engine::IComponent, public Engine::IDebuggableComponent
	{
	public:
		using ptr_Buff = std::unique_ptr<Buff>;

		RPGComponent(Engine::GameObject& obj, const RPGActorDef& rpgActorDef);
		~RPGComponent();

		void  VirtualOnActivated() override;

		void  Update(float dt) override;

		float GetStat(RPGStats stat);
		void  SetStatBase(RPGStats stat, float value);

		void  AddBuff(ptr_Buff buff);

		void  Debug(Engine::view::IViewStrategy* viewStrategy) override;

	private:
		void ResetModifiers();
		std::vector< ptr_Buff > m_buffs;

		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_statBase;
		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_additiveStatBonus;		// default 0
		std::array<float, static_cast<size_t>(RPGStats::COUNT)> m_percentageStatBonus;		// default 1
	};
}