#pragma once
#include "UIState.h"

#include <Engine/Managers/UIManager.h>

namespace Game
{

  class GameMenuState : public UIState
  {
  public:
    GameMenuState() = default;
    ~GameMenuState() = default;

    void OnCreate() override;
    void OnDestroy() override;
    void OnEscapeAction() override;

    // Button callbacks
    void NewGameButtonCallback();
    void SettingsButtonCallback();
    void BackToMenuButtonCallback();
    void QuitButtonCallback();

  private:

    tgui::VerticalLayout::Ptr m_menuLayout;

    tgui::Button::Ptr m_newGameButton;
    tgui::Button::Ptr m_settingsButton;
    tgui::Button::Ptr m_backToMenuButton;
    tgui::Button::Ptr m_quitButton;
  };

}