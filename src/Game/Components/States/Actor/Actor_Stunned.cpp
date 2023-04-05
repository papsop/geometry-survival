#include "Actor_Stunned.h"
#include <Engine/Components/View.h>

namespace Game
{

// 	Actor_Stunned::Actor_Stunned(Engine::PushdownStateMachine& parentStateMachine, ActorComponent* parentActor, float duration)
// 		: IState(parentStateMachine)
// 		, m_stunDuration(duration)
// 		, m_parentActor(parentActor)
// 		, m_stunTime(duration)
// 	{
// 		m_shapeViewComponent = m_parentActor->Owner.GetComponent<Engine::ShapeViewComponent>();
// 	}
// 
// 	void Actor_Stunned::OnTransitionIn()
// 	{
// 		if (m_shapeViewComponent != nullptr)
// 		{
// 			m_previousColor = m_shapeViewComponent->GetRenderable().shape.Color;
// 			m_shapeViewComponent->GetMutableRenderable().shape.Color = sf::Color::White;
// 		}
// 
// 		m_stunTime = m_stunDuration;
// 	}
// 
// 	void Actor_Stunned::OnTransitionOut()
// 	{
// 		if (m_shapeViewComponent != nullptr)
// 		{
// 			m_shapeViewComponent->GetMutableRenderable().shape.Color = m_previousColor;
// 		}
// 	}
// 
// 	void Actor_Stunned::Update(float dt)
// 	{
// 
// 		m_stunDuration -= dt;
// 		if (m_stunDuration <= 0.0f)
// 			m_parentStateMachine.PopState(); // go back to chasing
// 	}

}