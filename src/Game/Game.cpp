#include "GameInjection.h"

#include <windows.h>
#include <WinBase.h>
#include <iostream>
#include <pugixml.hpp>

int main()
{
    Game::GameInjection inj;
    Engine::Application::Instance().Run(inj);

    return 0;
}