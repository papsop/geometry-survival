#pragma once
#include "Buff.h"

namespace Game
{
	class BurningBuff : public Buff
	{
	public:
		BurningBuff(float duration, BuffTag tag = BuffTag::None);
		~BurningBuff() override = default;

		void OnInit() override;
		void OnDestroy() override;
		void VirtualUpdate(float dt) override;
	};
}