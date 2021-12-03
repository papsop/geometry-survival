#include "SquareComponent.h"

#include "SFML/Graphics.hpp"

#include "../../GameObject.h"

namespace Game
{
    SquareComponent::SquareComponent(GameObject &obj) : IRenderableComponent(obj)
    {
        m_renderManager = SingletonManager::Instance().GetRenderManager();

        m_transformComponent = obj.GetComponent<TransformComponent>();
    }

    void SquareComponent::Render()
    {
        if (auto tmp = m_transformComponent.lock())
        {
            // just placeholder to test it out
            sf::CircleShape shape(30.0f, 4);
            shape.setOrigin(sf::Vector2f(15.0f, 15.0f));
            shape.setPosition(tmp->GetPosition());
            shape.setScale(tmp->GetScale());
            shape.setFillColor(sf::Color::Green);
            m_renderManager->Draw(shape);
        }
    }
};