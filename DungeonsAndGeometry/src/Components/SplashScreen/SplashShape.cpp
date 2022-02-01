#include "SplashShape.h"
#include "Managers/SubsystemManager.h"

namespace Game
{
    SplashShape::SplashShape(Engine::GameObject& obj, size_t pointCount, sf::Color color, int zIndex)
        : IRenderableShapeComponent(obj, zIndex)
        , m_shape(obj.GetTransform())
    {
        m_shape.PointCount = pointCount;
        m_shape.Color = color;
        m_shape.Radius = 50;
        Engine::SubsystemManager::Get().RegisterComponent(this);
        Engine::SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
    }

    SplashShape::~SplashShape()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
        Engine::SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
    }

    void SplashShape::Update(float dt)
    {
        m_timeToDie -= dt;
        if (m_timeToDie <= 0.0f) Owner.Destroy();
    }
}