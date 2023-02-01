#pragma once
#include "ISkill.h"

namespace Game
{
	class Skill_PickupRadius : public ISkill
	{
	public:
		Skill_PickupRadius();
		~Skill_PickupRadius() = default;

		void Learn(Engine::GameObject* entity) override;
	};
}