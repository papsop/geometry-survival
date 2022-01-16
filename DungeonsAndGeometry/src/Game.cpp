#include "Application.h"
#include "GameInjection.h"
#include <iostream>

int main()
{
    std::unique_ptr<Game::GameInjection> inj = std::make_unique<Game::GameInjection>();

    Engine::Application::Instance().Run(*inj.get());

    return 0;
}