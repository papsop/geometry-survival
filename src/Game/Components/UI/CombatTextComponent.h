#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class CombatTextComponent : public Engine::IUIComponent
  {
  public:
    CombatTextComponent(Engine::GameObject& obj);
    ~CombatTextComponent() override = default;

  protected:
    void RegisterUIElements() override;
    void UIShown() override;
    void UIHidden() override;

  private:
  };
}