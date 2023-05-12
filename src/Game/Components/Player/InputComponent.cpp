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
      SetRequiredComponents<ActorComponent>();
  }

  void InputComponent::OnCreate()
  {
      Engine::ComponentManager::Get().RegisterComponent(this);
      m_actorComponent = Owner.GetComponent<ActorComponent>();
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
    // rotation
    auto b2MousePos = Engine::RenderManager::Get().pixelsPosToCoordsPos(m_inputManager.GetCursorPosition());
    float angle = Engine::math::AngleBetweenVecs(Owner.GetTransform()->GetPosition(), b2MousePos);

    m_actorComponent->AddCommand<RotateCommand>(angle);
    // movement
    float horizontal = m_inputManager.GetAxis(Engine::InputManager::Axis::Horizontal);
    float vertical = -m_inputManager.GetAxis(Engine::InputManager::Axis::Vertical);

    m_actorComponent->AddCommand<MoveCommand>(horizontal, vertical);
        
    // shooting
    if (m_inputManager.GetAction(Engine::InputManager::Action::Fire1).Pressed)
      m_actorComponent->AddCommand<FireCommand>();

		// reloading
		if (m_inputManager.GetAction(Engine::InputManager::Action::Reload).PressedThisFrame)
      m_actorComponent->AddCommand<ReloadCommand>();
  }

	void InputComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
    SetEnabled(eventData.NewState == GameState::Gameplay);
	}

};