#include "TransformComponent.h"
#include <iostream>

namespace Game
{
    TransformComponent::~TransformComponent()
    {
        std::cout << "~TransformComponent" << std::endl;
    }

    void TransformComponent::Update(float dt)
    {
        std::cout << "Updating Transform " << std::endl;
    }
};