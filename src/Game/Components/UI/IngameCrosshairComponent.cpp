#include "IngameCrosshairComponent.h"

#include <Engine/Components/Drawables/SpriteDrawableComponent.h>


namespace Game
{
	IngameCrosshairComponent::IngameCrosshairComponent(Engine::GameObject& obj)
		: IComponent(obj)
		, m_inputManager(Engine::InputManager::Get())
	{
		SetRequiredComponents<Engine::SpriteDrawableComponent>();
	}

	void IngameCrosshairComponent::VirtualOnCreate()
	{
		Engine::ComponentManager::Get().RegisterComponent(this);
	}

	IngameCrosshairComponent::~IngameCrosshairComponent()
	{
		Engine::ComponentManager::Get().UnregisterComponent(this);
	}

	void IngameCrosshairComponent::VirtualOnActivated()
	{
		Engine::IEventListener<event::E_GameStateChanged>::RegisterListener();
		Engine::RenderManager::Get().ShowMouse(false);
	}

	void IngameCrosshairComponent::VirtualOnDeactivated()
	{
		Engine::IEventListener<event::E_GameStateChanged>::UnregisterListener();

	}

	void IngameCrosshairComponent::Update(float dt)
	{
		auto b2MousePos = Engine::RenderManager::Get().pixelsPosToCoordsPos(m_inputManager.GetCursorPosition());
		Owner.GetTransform()->SetPosition(b2MousePos);
	}

	void IngameCrosshairComponent::ReceiveEvent(const event::E_GameStateChanged& eventData)
	{
		SetEnabled(eventData.NewState == GameState::Gameplay);

		//Owner.GetComponent<Engine::SpriteDrawableComponent>()->Deactivate();

		Engine::RenderManager::Get().ShowMouse(!IsEnabled());
	}

}