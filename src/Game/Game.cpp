#include "GameInjection.h"
#include <Engine/ImGui/imgui.h>
#include <Engine/ImGui/imgui-SFML.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main()
{

	Game::GameInjection inj;
	Engine::Application app;
	app.Run(inj);

  return 0;
}