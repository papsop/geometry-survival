#include "GameInjection.h"
#include <iostream>

int main()
{
    Game::GameInjection inj;
    Engine::Application app;
    app.Run(inj);

    return 0;
}

/*
TODO:
    - gameplay!
    - weapons system
        - multiple weapon parameters implementations
        - store these combinations in yaml file
    - nicer Application::HandleViewEvent
        - maybe use event system for these events

MAYBE ONE DAY:
    - message system between objects
        - currently supporting only global events
    - getting gameObjects by TAG
        - unity style https://docs.unity3d.com/Manual/Tags.html
        - useful for getting player when needed in other system

*/