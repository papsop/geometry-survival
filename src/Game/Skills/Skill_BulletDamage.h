#pragma once
#include "ISkill.h"

namespace Game
{
	class Skill_BulletDamage : public ISkill
	{
	public:
		Skill_BulletDamage();
		~Skill_BulletDamage() = default;

		void Learn(Engine::GameObject* entity) override;
	};
}