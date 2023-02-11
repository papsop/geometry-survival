#pragma once
#include <vector>
#include <functional>
#include "RPGStats.h"

namespace Game
{
	// forward
	class RPGComponent;

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
			MovementSlowAfterShooting,
			Burning,
		};

		Buff(float duration, BuffTag tag = BuffTag::None);
		virtual ~Buff() = default;

		virtual void OnInit() {};
		virtual void OnDestroy() {};
		void Update(float dt);	
		virtual void VirtualUpdate(float dt) {};

		bool ShouldDestroy() { return m_shouldDestroy; };
		BuffTag GetBuffTag();
		void SetOwnerRPGComponent(RPGComponent* owner);

		Buff& AddAdditiveModifier(RPGStats stat, float value);
		Buff& AddPercentageModifier(RPGStats stat, float value);

		const std::vector<BuffModifierEntry>& GetAdditiveModifiers() { return m_additiveBuffModifiers; };
		const std::vector<BuffModifierEntry>& GetPercentageModifiers() { return m_percentageBuffModifiers; };

	protected:
		RPGComponent* m_ownerRPGComponent = nullptr;
		BuffTag m_tag;
		float m_timer;

		bool m_isTimed;
		bool m_shouldDestroy;

		std::vector<BuffModifierEntry> m_additiveBuffModifiers;
		std::vector<BuffModifierEntry> m_percentageBuffModifiers;
	};
}