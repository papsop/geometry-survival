#pragma once
#include <Engine/Core/StateMachine/IState.h>
#include <Engine/Components/Core.h>
#include "../Actor/ActorComponent.h"

namespace Game
{
	class Actor_KnockedBack : public Engine::IState
	{
	public:
		Actor_KnockedBack(Engine::StateContainer& container, ActorComponent* actorComponent, Engine::Transform& source);
		~Actor_KnockedBack() = default;

		void OnInit() override;
		void OnDestroy() override;
		void OnReset() override;

		void Update(float dt) override;
		void ProcessMessage(const Engine::Message& message) override;
	private:
		ActorComponent* m_parentActor;
		Engine::Transform& m_source;
		float m_timeToRelease = 2.0f;
	};
}