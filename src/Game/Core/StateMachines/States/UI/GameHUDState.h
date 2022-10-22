#pragma once
#include "UIState.h"

namespace Game
{

  class GameHUDState : public UIState
  {
  public:
    GameHUDState() = default;
    ~GameHUDState() = default;

    void OnCreate() override;
    void OnDestroy() override;
    void OnEscapeAction() override;
  };

}