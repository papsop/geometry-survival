#pragma once
#include "GameObject/GameObject.h"
#include <SFML/System.hpp>

namespace Engine
{
	namespace event 
	{
		struct E_GameObjectDeleted
		{
			E_GameObjectDeleted(GameObjectID id) : ID(id) {};
			GameObjectID ID;
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
	}
}