#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include <Engine/Managers/UIManager.h>

namespace Game
{
  class MainMenuScreenComponent : public Engine::IImGuiComponent
  {
  public:
    MainMenuScreenComponent(Engine::GameObject& obj);
    ~MainMenuScreenComponent() override = default;


    // callbacks for buttons
    void PlayButtonCallback();
    void SettingsButtonCallback();
    void QuitButtonCallback();

    void Update(float dt) override;
  };
}