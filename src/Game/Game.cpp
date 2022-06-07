#include "GameInjection.h"
#include <iostream>
#include <vector>

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
        - enemy AI
            - spawner?
        - weapons system
        - health & damager system
    - nicer Application::HandleViewEvent
        - maybe use event system for these events

MAYBE ONE DAY:
    - nicer messaging system between objects
        - not sure what yet
    - better weapons system
		- multiple weapon parameters implementations
		- store these combinations in yaml file
    - getting gameObjects by TAG
        - unity style https://docs.unity3d.com/Manual/Tags.html
        - useful for getting player when needed in other system

NEW STUFF DONE:
    - simple messaging system
        - will be eventually refactored, but good enough for now to create some gameplay
*/