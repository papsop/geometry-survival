#include "GameInjection.h"

#include <windows.h>
#include <WinBase.h>
#include <iostream>

int main()
{
    Game::GameInjection inj;
    Engine::Application app;
    app.Run(inj);

    return 0;
}