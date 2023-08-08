#include "InputComponent.h"

#include <Engine/Application.h>
#include <Engine/Managers/RenderManager.h>
#include <Engine/Managers/ComponentManager.h>

namespace Game
{
  InputComponent::InputComponent(Engine::GameObject& obj)
      : IComponent(obj)
      , m_inputManager(Engine::InputManager::Get())
  {
      SetRequiredComponents<ActorComponent, WeaponComponent>();
  }

  void InputComponent::VirtualOnCreate()
  {
      Engine::ComponentManager::Get().RegisterComponent(this);
      m_actorComponent = Owner.GetComponent<ActorComponent>();
      m_weaponComponent = Owner.GetComponent<WeaponComponent>();
  }

  InputComponent::~InputComponent()
  {
      Engine::ComponentManager::Get().UnregisterComponent(this);
  }

	void InputComponent::VirtualOnActivated()
	{
		Engine::IEventListener<event::E_GameStateChanged>::RegisterListener();
	}

	void InputComponent::VirtualOnDeactivated()
	{
		Engine::IEventListener<event::E_GameStateChanged>::UnregisterListener();
	}

  void InputComponent::Update(float dt)
  {
    // shooting target
    auto b2MousePos = Engine::RenderManager::Get().pixelsPosToCoordsPos(m_inputManager.GetCursorPosition());
    m_weaponComponent->SetTargetPosition(b2MousePos);

    // movement
    float horizontal = m_inputManager.GetAxis(Engine::InputManager::Axis::Horizontal);
    float vertical = -m_inputManager.GetAxis(Engine::InputManager::Axis::Vertical);

    m_actorComponent->AddCommand<MoveCommand>(horizontal, vertical);
        
    // shooting
    if (m_inputManager.GetAction(Engine::InputManager::Action::Fire1).Pressed)
    {
      m_weaponComponent->Fire();
    }
  }

	void InputComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
    SetEnabled(eventData.NewState == GameState::Gameplay);
	}

};