#pragma once
#include "Buff.h"

namespace Game
{
	class FrozenBuff : public Buff
	{
	public:
		FrozenBuff(RPGComponent& owner, float duration, BuffTag tag = BuffTag::None);
		~FrozenBuff() override = default;

		void OnInit() override;
		void OnDestroy() override;
		void VirtualUpdate(float dt) override;
	};
}