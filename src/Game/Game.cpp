#include "GameInjection.h"

#include <windows.h>
#include <WinBase.h>
#include <iostream>

int main()
{
    Game::GameInjection inj;
    Engine::Application::Instance().Run(inj);

    return 0;
}