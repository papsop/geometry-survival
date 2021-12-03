#include "SpriteComponent.h"

#include "SFML/Graphics.hpp"
#include "../GameObject.h"

#include <iostream>
namespace Game
{
    SpriteComponent::SpriteComponent(GameObject &obj) : IRenderableComponent(obj)
    {
        m_renderManager = SingletonManager::Instance().GetRenderManager();
    }

    void SpriteComponent::Render()
    {
        std::cout << m_owner.DebugName << std::endl;
        // just placeholder to test it out
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        m_renderManager->Draw(shape);
    }
};