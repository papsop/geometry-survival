#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>

namespace Game
{
  class MainMenuScreenComponent : public Engine::IUIComponent
  {
  public:
    MainMenuScreenComponent(Engine::GameObject& obj);
    ~MainMenuScreenComponent() override = default;


    // callbacks for buttons
    void PlayButtonCallback();
    void QuitButtonCallback();

  protected:
    void RegisterUIElements() override;

  private:
    tgui::VerticalLayout::Ptr m_menuLayout;
    tgui::Button::Ptr m_playButton;
    tgui::Button::Ptr m_quitButton;

  };
}