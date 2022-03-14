#include "TriangleComponent.h"
#include "../../Application.h"
#include "../../Core/GameObject.h"

namespace Engine
{
    TriangleComponent::TriangleComponent(GameObject& obj, sf::Color color, int zIndex)
        : IRenderableShapeComponent(obj, zIndex)
        , m_shape(obj.GetTransform())
    {
        m_shape.PointCount = 3;
        m_defaultColor = color;
        m_shape.Color = color;
        m_shape.Radius = 50;   
    }

    void TriangleComponent::OnCreate()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    TriangleComponent::~TriangleComponent()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void TriangleComponent::OnCollision(GameObject& other)
    {
        m_shape.Color = sf::Color::Green;
    }

    const view::Shape& TriangleComponent::GetRenderableShape()
    {
        return m_shape;
    }
};