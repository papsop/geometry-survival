#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>
#include <Engine/Managers/ViewManager.h>
#include <Engine/Core/Events.h>
#include <Engine/Core/EventData.h>

#include "../../Core/EventData.h"

namespace Game
{
  class SettingsScreenComponent : public Engine::IImGuiComponent, public Engine::IEventListener<Engine::event::E_EscapeAction>
  {
  public:
    SettingsScreenComponent(Engine::GameObject& obj);
    ~SettingsScreenComponent() override = default;

    void BackToMenuCallback();
    void SaveSettingsCallback();

    void Update(float dt) override;

  protected:
    void ReceiveEvent(const Engine::event::E_EscapeAction& eventData) override;

    virtual void VirtualOnActivated();
    virtual void VirtualOnDeactivated();

  private:
    bool m_fullscreenVal = false;

    std::vector<Engine::ResolutionEntry> m_resolutions;
    unsigned int m_selectedResolution = 0;
  };
}