#include <Engine/Application.h>
#include <Game/GameInjection.h>

int main(void)
{
  Game::GameInjection inj;
  Engine::Application app;
  app.Run(inj);

  return 0;
}
