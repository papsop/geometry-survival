#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <array>
namespace Game
{
  class IngameUIControllerComponent : public Engine::IComponent
  {
  public:
    // Helpers
    // index = index in m_components
    enum class IngameUIState {HUD, SKILL_PICKER, MENU, SETTINGS, GAMEOVER, COUNT};

    // Class members

    IngameUIControllerComponent(Engine::GameObject& obj);
    ~IngameUIControllerComponent() = default;

    void SetState(IngameUIState newState);

  protected:
    void VirtualOnActivated() override;

  private:
    IngameUIState m_currentState = IngameUIState::HUD;
    std::array<IComponent*, static_cast<size_t>(IngameUIState::COUNT)> m_components;

  };
}