#include "AmmoHUDComponent.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Application.h>
#include "../../Managers/GameManager.h"

namespace Game
{

  AmmoHUDComponent::AmmoHUDComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {

  }

  void AmmoHUDComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);

    auto* gameManager = Engine::Application::Instance().GetGameManager<GameManager>();
    m_playerWeaponComponent = gameManager->GetPlayerGameObject()->GetComponent<WeaponComponent>();
  }

  AmmoHUDComponent::~AmmoHUDComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void AmmoHUDComponent::Update(float dt)
  {
    if (m_playerWeaponComponent)
    {
      std::string text = std::to_string(m_playerWeaponComponent->GetCurrentAmmo()) + "/" + std::to_string(m_playerWeaponComponent->GetMaxAmmo());
      Owner.GetComponent<Engine::TextViewComponent>()->SetText(text);
    }
  }

};