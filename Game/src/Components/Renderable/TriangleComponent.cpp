#include "TriangleComponent.h"

#include "SFML/Graphics.hpp"

#include "../../GameObject.h"

namespace Game
{
    TriangleComponent::TriangleComponent(GameObject& obj) : IRenderableComponent(obj)
    {
        m_renderManager = SingletonManager::Instance().GetRenderManager();

        m_transformComponent = obj.GetComponent<TransformComponent>();
    }

    void TriangleComponent::Render()
    {
        if (auto tmp = m_transformComponent.lock())
        {
            // just placeholder to test it out
            sf::CircleShape shape(50.0f, 3);
            shape.setOrigin(sf::Vector2f(25.0f, 25.0f));
            shape.setPosition(tmp->GetPosition());
            shape.setScale(tmp->GetScale());
            shape.setFillColor(sf::Color::Red);
            m_renderManager->Draw(shape);
        }
    }
};