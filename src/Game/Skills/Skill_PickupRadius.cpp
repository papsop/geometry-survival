#include "Skill_PickupRadius.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{

	Skill_PickupRadius::Skill_PickupRadius()
		: ISkill("+3 pickup radius", "")
	{
	}

	void Skill_PickupRadius::Learn(Engine::GameObject* entity)
	{
		// using BuffTag::None so we can stack this buff instead of overwriting
		auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
		skillBuff->AddAdditiveModifier(RPGStats::PICKUP_FIELD_SIZE, 3);

		auto* rpg = entity->GetComponent<RPGComponent>();

		if (rpg)
		{
			rpg->AddBuff(std::move(skillBuff));
		}

		LOG_INFO("Learning PickupRadius");
	}

}