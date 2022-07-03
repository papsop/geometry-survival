#pragma once

namespace Game
{
	class Buff
	{
	public:
		Buff();
		~Buff() = default;

		virtual void OnInit() {};
		virtual void OnDestroy() {};
		void Update(float dt);	
		virtual void VirtualUpdate(float dt) {};

		bool ShouldDestroy() { return m_shouldDestroy; };
	private:
		bool m_isInfinite;

		float m_timer;
		bool m_shouldDestroy;
	};
}