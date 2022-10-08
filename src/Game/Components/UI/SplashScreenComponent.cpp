#include "SplashScreenComponent.h"
#include <Engine/Managers/SceneManager.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Managers/ComponentManager.h>
#include "../../Scenes/MainMenuScene.h"

namespace Game
{

  SplashScreenComponent::SplashScreenComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {

  }

  void SplashScreenComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);
    auto* gui = Engine::UIManager::Get().GetGui();
    if (gui)
    {
      m_splashLabel = tgui::Label::create("Geometry survival");
      m_splashLabel->setOrigin(0.5f, 0.5f);
      m_splashLabel->setPosition("50%", "50%");
      m_splashLabel->setTextSize(48);
      m_splashLabel->setVisible(Owner.IsActive());

      gui->add(m_splashLabel);
    }

  }

  void SplashScreenComponent::OnDestroy()
  {
    auto* gui = Engine::UIManager::Get().GetGui();
    if (gui)
    {
      gui->remove(m_splashLabel);
    }
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void SplashScreenComponent::VirtualOnActivated()
  {
    m_splashLabel->setVisible(true);
  }

  void SplashScreenComponent::VirtualOnDeactivated()
  {
    m_splashLabel->setVisible(false);
  }

  void SplashScreenComponent::HandleSwitchToMainMenu()
  {
    Engine::SceneManager::Get().LoadSceneDestroyPrevious(MainMenuScene());
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