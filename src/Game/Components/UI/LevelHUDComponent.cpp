#include "LevelHUDComponent.h"
#include "../../Managers/GameManager.h"

#include <Engine/Application.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{

  LevelHUDComponent::LevelHUDComponent(Engine::GameObject& obj)
    : IComponent(obj)
  {
  }

  void LevelHUDComponent::OnCreate()
  {
    Engine::ComponentManager::Get().RegisterComponent(this);

    auto* gameManager = Engine::Application::Instance().GetGameManager<GameManager>();
    m_playerLevelComponent = gameManager->GetPlayerGameObject()->GetComponent<LevelComponent>();
  }

  LevelHUDComponent::~LevelHUDComponent()
  {
    Engine::ComponentManager::Get().UnregisterComponent(this);
  }

  void LevelHUDComponent::Update(float dt)
  {
    if (m_playerLevelComponent != nullptr)
    {
      std::string text = std::to_string(m_playerLevelComponent->GetCurrentLevel()) + " level";
      Owner.GetComponent<Engine::TextViewComponent>()->SetText(text);
    }
  }

}