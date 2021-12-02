#include "SpriteComponent.h"

#include "SFML/Graphics.hpp"


namespace Game
{
    SpriteComponent::SpriteComponent(GameObject &obj) : IRenderableComponent(obj)
    {
        m_renderManager = SingletonManager::Instance().GetRenderManager();
    }

    void SpriteComponent::Render()
    {
        // just placeholder to test it out
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        m_renderManager->Draw(shape);
    }
};