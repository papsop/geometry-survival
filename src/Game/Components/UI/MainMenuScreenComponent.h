#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>

namespace Game
{
  class MainMenuScreenComponent : public Engine::IComponent
  {
  public:
    MainMenuScreenComponent(Engine::GameObject& obj);
    ~MainMenuScreenComponent() override = default;

    void OnCreate() override;
    void OnDestroy() override;

    // callbacks for buttons
    void PlayButtonCallback();
    void QuitButtonCallback();


  private:
    tgui::VerticalLayout::Ptr m_menuLayout;
    tgui::Button::Ptr m_playButton;
    tgui::Button::Ptr m_quitButton;
  };
}