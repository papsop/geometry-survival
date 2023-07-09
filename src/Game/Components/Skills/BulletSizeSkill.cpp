#include "BulletSizeSkill.h"
#include "SkillsComponent.h"
#include "../Actor/WeaponComponent.h"

namespace Game
{

	BulletSizeSkill::BulletSizeSkill()
		: ISkill("BulletSizeSkill")
	{

	}

	void BulletSizeSkill::Init(SkillsComponent& ownerComp)
	{
		m_weaponComponent = ownerComp.Owner.GetComponent<WeaponComponent>();

		m_weaponComponent->RegisterBulletMiddleware(this);
	}

	void BulletSizeSkill::Clear(SkillsComponent& ownerComp)
	{
		m_weaponComponent->UnregisterBulletMiddleware(this);
	}

	void BulletSizeSkill::Middleware(Engine::GameObject& bullet)
	{
		LOG_ERROR("MODIFYING BULLET");
	}

}