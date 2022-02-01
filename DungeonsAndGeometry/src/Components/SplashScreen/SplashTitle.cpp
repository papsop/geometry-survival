#include "SplashTitle.h"
#include "Managers/SubsystemManager.h"

namespace Game
{

    SplashTitle::SplashTitle(Engine::GameObject& obj)
        : IRenderableTextComponent(obj)
        , m_text(obj.GetTransform())
    {
        m_text.Color = sf::Color::Color(80, 80, 80, 255);
        m_text.Value = "Dungeons & Geometry";
        m_text.Size = 72;
        m_text.ShouldCenter = true;
        Engine::SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
    }

    SplashTitle::~SplashTitle()
    {
        Engine::SubsystemManager::Get().GetViewSubsystem().UnregisterComponent(this);
    }

    const Engine::view::Text& SplashTitle::GetRenderableText()
    {
        return m_text;
    }
}