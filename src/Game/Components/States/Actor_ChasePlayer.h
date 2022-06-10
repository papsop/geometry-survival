#pragma once
#include <Engine/Core/StateMachine/IState.h>

namespace Game
{
	class Actor_ChasePlayer : public Engine::IState
	{
	public:
		Actor_ChasePlayer() = default;
		~Actor_ChasePlayer() = default;

		void OnInit() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;

	};
}