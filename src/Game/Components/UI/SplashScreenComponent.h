#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class SplashScreenComponent : public Engine::IUIComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    SplashScreenComponent(Engine::GameObject& obj);
    ~SplashScreenComponent() override = default;

    void Update(float dt) override;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;
    void RegisterUIElements() override {};

    void UIShown() override;
    void UIHidden() override;

  private:
    void HandleSwitchToMainMenu();
    float m_splashTimer = 3.0f;
  };
}