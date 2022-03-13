#include "IComponent.h"

#include "../../Core/GameObject.h"
#include "../../Application.h"

namespace Engine
{

    // physics
    IColliderComponent::IColliderComponent(GameObject& obj, CollisionLayer layer)
        : IComponent(obj)
        , c_layer(layer)
    {
        //Engine::SubsystemManager::Get().GetPhysicsSubsystem().RegisterComponent(this);
    }

    IColliderComponent::~IColliderComponent()
    {
        Engine::SubsystemManager::Get().GetPhysicsSubsystem().UnregisterComponent(this);
    }

    void IColliderComponent::SetRelativePosition(sf::Vector2f position) 
    { 
        m_relativePosition = position; 
    }

    sf::Vector2f IColliderComponent::GetRelativePosition() const 
    {
        return m_relativePosition; 
    }

    sf::Vector2f IColliderComponent::GetAbsolutePosition() const 
    {
        return Owner.GetTransform().Position + m_relativePosition;
    }

    // view

    IRenderableShapeComponent::IRenderableShapeComponent(GameObject& obj, int zIndex)
        : IComponent(obj)
        , ZIndex(zIndex)
        , m_ownerTransform(obj.GetTransform())
    {};

    IRenderableTextComponent::IRenderableTextComponent(GameObject& obj)
        : IComponent(obj)
        , m_ownerTransform(obj.GetTransform())
    {};
};