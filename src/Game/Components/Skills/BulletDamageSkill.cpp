#include "BulletDamageSkill.h"
#include "SkillsComponent.h"
#include "../Actor/WeaponComponent.h"
#include "../Actor/BulletComponent.h"

#include <Engine/Components/Drawables/SpriteDrawableComponent.h>

namespace Game
{

	BulletDamageSkill::BulletDamageSkill()
		: ISkill("BulletSizeSkill")
	{

	}

	void BulletDamageSkill::Init(SkillsComponent& ownerComp)
	{
		m_weaponComponent = ownerComp.Owner.GetComponent<WeaponComponent>();

		m_weaponComponent->RegisterBulletMiddleware(this);
	}

	void BulletDamageSkill::Clear(SkillsComponent& ownerComp)
	{
		m_weaponComponent->UnregisterBulletMiddleware(this);
	}

	void BulletDamageSkill::Middleware(Engine::GameObject& bullet)
	{
		//auto* bulletComp = bullet.GetComponent<BulletComponent>();
		//bulletComp->SetDamage(20.0);
	}

}