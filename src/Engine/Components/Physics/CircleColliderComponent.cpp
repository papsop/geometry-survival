#include "CircleColliderComponent.h"
#include "../../Core/GameObject.h"

namespace Engine
{
    CircleColliderComponent::CircleColliderComponent(GameObject& obj, float radius)
        : IColliderComponent(obj, IColliderComponent::CollisionLayer::GameplayArea)
        , m_radius(radius)
    {
    }

    ColliderData CircleColliderComponent::GetColliderData()
    {
        ColliderData data;
        CircleColliderData ccData(m_radius, GetAbsolutePosition());
        data.CircleColliders.push_back(ccData);
        return data;
    }

    void CircleColliderComponent::Debug(view::IViewStrategy* viewStrategy)
    {
        Transform t;
        t.Position = GetAbsolutePosition();
        auto circle = view::Circle(t);
        circle.Radius = m_radius;
        circle.FillColor = sf::Color(0, 0, 0, 0);
        circle.OutlineColor = sf::Color(255, 255, 255, 255);
        circle.OutlineThickness = 3.0f;

        viewStrategy->Render(circle);
    }
}