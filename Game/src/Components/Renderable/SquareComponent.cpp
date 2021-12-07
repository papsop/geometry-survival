#include "SquareComponent.h"

#include "SFML/Graphics.hpp"

#include "../../GameObject.h"

#include <iostream>
namespace Game
{
    SquareComponent::SquareComponent(GameObject &obj, int zIndex) 
        : IRenderableComponent(obj, zIndex)
    {
        m_shape = std::make_shared<sf::CircleShape>(30.0f, 4);
        m_shape->setOrigin(sf::Vector2f(30.0f, 30.0f));
        m_shape->setFillColor(sf::Color::Green);
    }

    void SquareComponent::Init() {}

    void SquareComponent::Render()
    {
        Transform& transform = m_owner.GetTransform();
        m_shape->setPosition(transform.Position);
        m_shape->setScale(transform.Scale);
        m_shape->setRotation(transform.Rotation);
        m_renderManager->RequestRender(m_zIndex, m_shape.get());
    }
};