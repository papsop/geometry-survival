#include "TriangleComponent.h"

#include "SFML/Graphics.hpp"

#include "../../GameObject.h"

namespace Game
{
    //TriangleComponent::TriangleComponent(GameObject& obj, int zIndex) 
    //    : IRenderableComponent(obj, zIndex)
    //{
    //    m_shape = std::make_shared<sf::CircleShape>(30.0f, 3);
    //    m_shape->setOrigin(sf::Vector2f(30.0f, 30.0f));
    //    m_shape->setFillColor(sf::Color::Red);
    //}

    //void TriangleComponent::Init() {}

    //void TriangleComponent::Render()
    //{
    //    Transform& transform = m_owner.GetTransform();
    //    m_shape->setPosition(transform.Position);
    //    m_shape->setScale(transform.Scale);
    //    m_shape->setRotation(transform.Rotation);
    //    m_renderManager->RequestRender(m_zIndex, m_shape.get());
    //}
};