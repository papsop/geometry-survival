#include "SplashBackground.h"
#include <Engine/Managers/SubsystemManager.h>

namespace Game
{
    SplashBackground::SplashBackground(Engine::GameObject& obj)
        : IRenderableShapeComponent(obj, 10000)
        , m_shape(obj.GetTransform())
    {
        m_shape.PointCount = 3;
        m_shape.Color = sf::Color::Color(20, 20, 20, 255);
        m_shape.Radius = 10000;
        Engine::SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
    }

    SplashBackground::~SplashBackground()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
    }

    const Engine::view::Shape& SplashBackground::GetRenderableShape()
    {
        return m_shape;
    }
}