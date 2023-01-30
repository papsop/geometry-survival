#include "Skill_BulletDamage.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{

	Skill_BulletDamage::Skill_BulletDamage()
		: ISkill("+3 bullet damage", "")
	{
	}

	void Skill_BulletDamage::Learn(Engine::GameObject* entity)
	{
		// using BuffTag::None so we can stack this buff instead of overwriting
		auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
		skillBuff->AddAdditiveModifier(RPGStats::WEAPON_DAMAGE, 3);

		auto* rpg = entity->GetComponent<RPGComponent>();

		if (rpg)
		{
			rpg->AddBuff(std::move(skillBuff));
		}

		LOG_INFO("Learning BulletDamage");
	}

}