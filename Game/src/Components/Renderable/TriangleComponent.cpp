#include "TriangleComponent.h"

#include "SFML/Graphics.hpp"

#include "../../GameObject.h"

namespace Game
{
    TriangleComponent::TriangleComponent(GameObject& obj, int zIndex) : IRenderableComponent(obj, zIndex)
    {
        m_renderManager = SingletonManager::Instance().GetRenderManager();

        m_shape = std::make_shared<sf::CircleShape>(30.0f, 3);
        m_shape->setOrigin(sf::Vector2f(15.0f, 15.0f));
        m_shape->setFillColor(sf::Color::Red);
    }

    void TriangleComponent::Init()
    {
        m_transformComponent = m_owner.GetComponent<TransformComponent>();
    }

    void TriangleComponent::Render()
    {
        if (auto tmpTransform = m_transformComponent.lock())
        {
            m_shape->setPosition(tmpTransform->GetPosition());
            m_shape->setScale(tmpTransform->GetScale());
            m_renderManager->RequestRender(m_zIndex, m_shape);
        }
    }
};