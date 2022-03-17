#include "CircleColliderComponent.h"
#include "../../Core/GameObject.h"

namespace Engine
{
    CircleColliderComponent::CircleColliderComponent(GameObject& obj, float radius)
        : IColliderComponent(obj, IColliderComponent::CollisionLayer::GameplayArea)
        , m_radius(radius)
    {
    }

    ColliderData CircleColliderComponent::GetColliderData() const
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

        // aabb
        auto circleBoundingBox = GetColliderData().CircleColliders[0].GetBoundingBox();
        // Top
        view::Line lineTop;
        lineTop.Points[0] = sf::Vector2f(circleBoundingBox.left, circleBoundingBox.top);
        lineTop.Points[1] = sf::Vector2f(circleBoundingBox.left + circleBoundingBox.width, circleBoundingBox.top);
        // Bottom
        view::Line lineBottom;
        lineBottom.Points[0] = sf::Vector2f(circleBoundingBox.left, circleBoundingBox.top + circleBoundingBox.height);
        lineBottom.Points[1] = sf::Vector2f(circleBoundingBox.left + circleBoundingBox.width, circleBoundingBox.top + circleBoundingBox.height);
        // Left
        view::Line lineLeft;
        lineLeft.Points[0] = sf::Vector2f(circleBoundingBox.left, circleBoundingBox.top);
        lineLeft.Points[1] = sf::Vector2f(circleBoundingBox.left, circleBoundingBox.top + circleBoundingBox.height);
        // Right
        view::Line lineRight;
        lineRight.Points[0] = sf::Vector2f(circleBoundingBox.left + circleBoundingBox.width, circleBoundingBox.top);
        lineRight.Points[1] = sf::Vector2f(circleBoundingBox.left + circleBoundingBox.width, circleBoundingBox.top + circleBoundingBox.height);

        viewStrategy->Render(lineTop);
        viewStrategy->Render(lineBottom);
        viewStrategy->Render(lineLeft);
        viewStrategy->Render(lineRight);
    }
}