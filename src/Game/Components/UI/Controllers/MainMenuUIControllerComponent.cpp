#include "MainMenuUIControllerComponent.h"
#include "../MainMenuScreenComponent.h"
#include "../SettingsScreenComponent.h"
namespace Game {

	MainMenuUIControllerComponent::MainMenuUIControllerComponent(Engine::GameObject& obj)
		: IComponent(obj)
	{

	}

	void MainMenuUIControllerComponent::VirtualOnActivated()
	{
		m_components[0] = Owner.GetComponent<MainMenuScreenComponent>();
		m_components[1] = Owner.GetComponent<SettingsScreenComponent>();

		SetState(MainMenuUIStates::MENU);
	}

	void MainMenuUIControllerComponent::SetState(MainMenuUIStates newState)
	{
		if (m_currentState == newState) return;

		LOG_WARN("Swapping mainMenuUIController state, new: %d", static_cast<size_t>(newState));

		for (auto& c : m_components)
		{
			if (c)
			{
				c->Deactivate();
			}

		}
		m_currentState = newState;
		m_components[static_cast<size_t>(newState)]->Activate();
	}

}