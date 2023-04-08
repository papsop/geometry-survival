#include "Skill_Scatter.h"
#include <Engine/Debug/Logger.h>
#include "../Core/RPG/Buff.h"
#include "../Components/Actor/RPGComponent.h"

namespace Game
{

	Skill_Scatter::Skill_Scatter()
		: ISkill("Enemy scatter", "+1 enemy scatter")
	{
	}

	void Skill_Scatter::Learn(Engine::GameObject* entity)
	{
		// using BuffTag::None so we can stack this buff instead of overwriting
		auto skillBuff = std::make_unique<Buff>(-1, Buff::BuffTag::None);
		skillBuff->AddAdditiveModifier(RPGStats::SCATTERS, 1);

		auto* rpg = entity->GetComponent<RPGComponent>();

		if (rpg)
		{
			rpg->AddBuff(std::move(skillBuff));
		}

		LOG_INFO("Learning Scatter");
	}

}
