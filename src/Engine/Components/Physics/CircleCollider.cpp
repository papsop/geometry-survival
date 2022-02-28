#include "CircleCollider.h"

namespace Engine
{
    CircleCollider::CircleCollider(GameObject& obj)
        : IColliderComponent(obj)
    {

    }

    void CircleCollider::Update(float dt)
    {

    }

    void CircleCollider::Debug(view::IViewStrategy* viewStrategy)
    {
        Transform t;
        t.Position = GetAbsolutePosition();
        auto circle = view::Shape(t);
        circle.PointCount = 30;
        circle.Radius = m_radius;
        circle.Color = sf::Color::Green;

        viewStrategy->Render(circle);
    }
}