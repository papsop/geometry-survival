#include "SplashScreenComponent.h"
#include <Engine/Managers/SceneManager.h>
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Application.h>

#include "../../Managers/GameManager.h"
#include "../../Scenes/MainMenuScene.h"

namespace Game
{

  SplashScreenComponent::SplashScreenComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {

  }

  void SplashScreenComponent::UIShown()
  {
    IEventListener<Engine::event::E_EscapeAction>::RegisterListener();
  }

  void SplashScreenComponent::UIHidden()
  {
    IEventListener<Engine::event::E_EscapeAction>::UnregisterListener();
  }

  void SplashScreenComponent::HandleSwitchToMainMenu()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->GoMainMenu();
  }

  void SplashScreenComponent::Update(float dt)
  {
    m_splashTimer -= dt;
    if (m_splashTimer < 0.0f)
    {
      HandleSwitchToMainMenu();
    }
  }

  void SplashScreenComponent::ReceiveEvent(const Engine::event::E_EscapeAction& eventData)
  {
    HandleSwitchToMainMenu();
  }

}