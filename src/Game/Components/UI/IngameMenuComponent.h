#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

namespace Game
{
  class IngameMenuComponent : public Engine::IImGuiComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    IngameMenuComponent(Engine::GameObject& obj);
    ~IngameMenuComponent() override = default;


    // Button callbacks
    void NewGameButtonCallback();
    void SettingsButtonCallback();
    void BackToMenuButtonCallback();
    void QuitButtonCallback();

    void Update(float dt) override;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    void VirtualOnActivated() override;
    void VirtualOnDeactivated() override;
  };
}