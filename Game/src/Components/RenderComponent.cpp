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

    void RenderComponent::Render()
    {
        // just placeholder to test it out
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        m_renderManager->Draw(shape);
    }
};