#include "GameInjection.h"
#include <iostream>
#include <vector>
#include <memory>

int main()
{
	Game::GameInjection inj;
	Engine::Application app;
	app.Run(inj);


    return 0;
}

/*

MAYBE ONE DAY:
    - nicer messaging system between objects
        - not sure what yet
    - better weapons system
		- multiple weapon parameters implementations
		- store these combinations in yaml file
    - getting gameObjects by TAG
        - unity style https://docs.unity3d.com/Manual/Tags.html
        - useful for getting player when needed in other system
*/