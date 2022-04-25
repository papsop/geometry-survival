#include "SplashTitle.h"
#include <Engine/Managers/SubsystemManager.h>

namespace Game
{

    SplashTitle::SplashTitle(Engine::GameObject& obj)
        : IRenderableTextComponent(obj)
        , m_text(&obj.GetTransform())
    {
        m_text.Color = sf::Color::Color(80, 80, 80, 255);
        m_text.Value = "Dungeons & Geometry";
        m_text.Size = 72;
        m_text.ShouldCenter = true;
    }

    void SplashTitle::OnCreate()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
    }

    SplashTitle::~SplashTitle()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
    }

}