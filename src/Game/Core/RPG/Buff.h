#pragma once
#include <vector>
#include <functional>
#include "RPGStats.h"

namespace Game
{

	struct BuffModifierEntry
	{
		RPGStats Stat;
		float ValueModifier;

		BuffModifierEntry(RPGStats stat, float val)
			: Stat(stat)
			, ValueModifier(val) {};
	};

	class Buff
	{
	public:

		enum class BuffTag
		{
			None,
			MovementSlowAfterShooting
		};

		using IterateFunction = std::function<void(const BuffModifierEntry&)>;

		Buff(float duration, BuffTag tag = BuffTag::None);
		~Buff() = default;

		virtual void OnInit() {};
		virtual void OnDestroy() {};
		void Update(float dt);	
		virtual void VirtualUpdate(float dt) {};

		bool ShouldDestroy() { return m_shouldDestroy; };

		Buff& AddModifier(RPGStats stat, float value);
		void IterateOverModifiers(IterateFunction func);
		BuffTag GetBuffTag();
	private:
		bool m_isTimed;
		BuffTag m_tag;
		float m_timer;
		bool m_shouldDestroy;
		std::vector<BuffModifierEntry> m_buffModifiers;
	};
}