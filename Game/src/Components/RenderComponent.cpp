#include "RenderComponent.h"

#include <iostream>

namespace Game
{
    RenderComponent::~RenderComponent()
    {
        std::cout << "~RenderComponent" << std::endl;
    }

    void RenderComponent::Update(float dt)
    {
        std::cout << "Updating RenderComponent" << std::endl;
    }
};