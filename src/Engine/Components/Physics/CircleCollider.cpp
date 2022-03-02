#include "CircleCollider.h"
#include "../../Core/GameObject.h"

namespace Engine
{
    CircleCollider::CircleCollider(GameObject& obj, float radius)
        : IColliderComponent(obj, IColliderComponent::LayerType::GameplayArea)
        , m_radius(radius)
    {
    }

    void CircleCollider::Update(float dt)
    {

    }

    void CircleCollider::Debug(view::IViewStrategy* viewStrategy)
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