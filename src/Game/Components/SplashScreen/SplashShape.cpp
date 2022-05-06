#include "SplashShape.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
    SplashShape::SplashShape(Engine::GameObject& obj, size_t pointCount, sf::Color color, int zIndex)
        : IRenderableShapeComponent(obj, Engine::view::RENDERABLE_TYPE::SHAPE, zIndex)
        , m_shape(&obj.GetTransform())
    {
        m_shape.PointCount = pointCount;
        m_shape.Color = color;
        m_shape.Radius = 50;
    }

    void SplashShape::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
        Engine::ViewManager::Get().RegisterComponent(this);
    }

    SplashShape::~SplashShape()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
        Engine::ViewManager::Get().UnregisterComponent(this);
    }

    void SplashShape::Update(float dt)
    {
        m_timeToDie -= dt;
        if (m_timeToDie <= 0.0f) Owner.Destroy();
    }
}