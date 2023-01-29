#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class CombatTextComponent : public Engine::IComponent
	{
	public:
		CombatTextComponent(Engine::GameObject& obj, float duration);
		~CombatTextComponent() = default;

		void OnCreate() override;
		void OnDestroy() override;
		void Update(float dt) override;

	private:
		float m_durationLeft;
	};
}