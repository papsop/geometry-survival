#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>
#include "../Actor/WeaponComponent.h"

namespace Game
{
  class AmmoHUDComponent : public Engine::IComponent
  {
  public:
    AmmoHUDComponent(Engine::GameObject& obj);
    ~AmmoHUDComponent() override;

    void OnCreate() override;
    void Update(float dt) override;
  private:
    WeaponComponent* m_playerWeaponComponent = nullptr;
  };
};