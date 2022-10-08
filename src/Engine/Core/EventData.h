#pragma once
#include <SFML/Window.hpp>

namespace Engine
{
	namespace event 
	{
		struct E_GameObjectDeleted
		{
			E_GameObjectDeleted(uint32_t id) : ID(id) {};
			uint32_t ID;
		};

		struct E_SFMLEvent
		{
			E_SFMLEvent(const sf::Event& event) : Event(event) { Type = event.type; };
			const sf::Event& Event;
			sf::Event::EventType Type;
		};

		struct E_ApplicationStopped {};

		struct E_WindowClosed {};
		struct E_OnConsoleKeyAction {};
		struct E_OnShowDebugKeyAction {};
		struct E_EscapeAction {};
	}
}