#pragma once
#include "ISkill.h"

namespace Game
{
	class Skill_Scatter : public ISkill
	{
	public:
		Skill_Scatter();
		~Skill_Scatter() = default;

		void Learn(Engine::GameObject* entity) override;
	};
}