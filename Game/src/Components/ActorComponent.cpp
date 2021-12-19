#include "ActorComponent.h"

#include "../GameObject.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include<math.h>

namespace Game
{

    ActorComponent::ActorComponent(GameObject &obj) 
        : IComponent(obj)
    {
    }

    void ActorComponent::OnGameObjectChanged()
    {
        m_rigidbodyComponent = m_owner.GetComponent<RigidbodyComponent>();
    }

    void ActorComponent::AddCommand(ICommand& command)
    {
        command.Execute(*this);
    }
     
    void ActorComponent::Move(float dX, float dY)
    {
        if (auto tmp = m_rigidbodyComponent.lock())
            tmp->Velocity = sf::Vector2f(dX, dY) * m_movementSpeed;
    }

    void ActorComponent::Update(float dt)
    {
    }
};