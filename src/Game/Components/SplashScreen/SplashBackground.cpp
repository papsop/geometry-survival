#include "SplashBackground.h"
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
    SplashBackground::SplashBackground(Engine::GameObject& obj)
		: IRenderableShapeComponent(obj, Engine::view::Renderable_Type::SHAPE, Engine::view::Layer::BACKGROUND)
		, m_shape(&obj.GetTransform())
    {
        m_shape.PointCount = 3;
        m_shape.Color = sf::Color::Color(20, 20, 20, 255);
        m_shape.Radius = 10000;
    }

    void SplashBackground::OnCreate()
    {
        Engine::ViewManager::Get().RegisterComponent(this);
    }

    SplashBackground::~SplashBackground()
    {
        Engine::ViewManager::Get().UnregisterComponent(this);
    }
}