#include "TransformComponent.h"
#include <iostream>

namespace Game
{
    void TransformComponent::Update(float dt)
    {
        m_position += m_velocity * dt;
    }
};