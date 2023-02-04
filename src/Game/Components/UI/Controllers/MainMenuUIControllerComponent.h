#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/GameObject/GameObject.h>

#include <array>
namespace Game
{
	class MainMenuUIControllerComponent : public Engine::IComponent
	{
	public:
		// Helpers
		// index = index in m_components
		enum class MainMenuUIStates { MENU, SETTINGS, COUNT };

		// Class members

		MainMenuUIControllerComponent(Engine::GameObject& obj);
		~MainMenuUIControllerComponent() = default;

		void SetState(MainMenuUIStates newState);

	protected:
		void VirtualOnActivated() override;

	private:
		MainMenuUIStates m_currentState = MainMenuUIStates::COUNT;
		std::array<IComponent*, static_cast<size_t>(MainMenuUIStates::COUNT)> m_components;

	};
}