#pragma once
#include "ISkill.h"
#include "../Actor/IBulletMiddleware.h"

namespace Game
{
	class WeaponComponent;

	class BulletDamageSkill : public ISkill, public IBulletMiddleware
	{
	public:
		BulletDamageSkill();
		void Init(SkillsComponent& ownerComp) override;
		void Clear(SkillsComponent& ownerComp) override;

		void Middleware(Engine::GameObject& bullet) override;

	private:
		WeaponComponent* m_weaponComponent = nullptr;
	};
}