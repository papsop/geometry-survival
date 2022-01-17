#include "GameInjection.h"
#include <iostream>

int main()
{
    Game::GameInjection inj;
    Engine::Application::Instance().Run(inj);

    return 0;
}