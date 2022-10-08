#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class GameMenuComponent : public Engine::IComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    GameMenuComponent(Engine::GameObject& obj);
    ~GameMenuComponent() override = default;

    void OnCreate() override;
    void OnDestroy() override;

    // Button callbacks
    void NewGameButtonCallback();
    void SettingsButtonCallback();
    void BackToMenuButtonCallback();
    void QuitButtonCallback();


  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;

  private:
    void SendMainMenuEvent();

    tgui::VerticalLayout::Ptr m_menuLayout;
    
    tgui::Button::Ptr m_newGameButton;
    tgui::Button::Ptr m_settingsButton;
    tgui::Button::Ptr m_backToMenuButton;
    tgui::Button::Ptr m_quitButton;
  };
}