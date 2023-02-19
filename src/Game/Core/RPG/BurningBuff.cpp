#include "BurningBuff.h"
#include "../../Components/Actor/ActorComponent.h"

namespace Game
{

	BurningBuff::BurningBuff(float duration, float damagePerTick, BuffTag tag /*= BuffTag::None*/) 
		: Buff(duration, tag)
		, m_damagePerTick(damagePerTick)
	{

	}

	void BurningBuff::OnInit()
	{

	}

	void BurningBuff::OnDestroy()
	{

	}

	void BurningBuff::VirtualUpdate(float dt)
	{
		m_burningTimer -= dt;

		if (m_burningTimer <= 0.0f)
		{
			// apply damage
			auto* ownerActorComponent= m_ownerRPGComponent->Owner.GetComponent<ActorComponent>();
			ownerActorComponent->ApplyDamage(m_damagePerTick, Actor_DamageSource::DOT);
			m_burningTimer = c_dotTimer;
		}
	}

}