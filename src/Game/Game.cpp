#include "GameInjection.h"

int main()
{
	Game::GameInjection inj;
	Engine::Application app;
	app.Run(inj);

  return 0;
}