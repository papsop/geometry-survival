#pragma once
#include "../Application.h"

namespace Game
{
    class RenderManager
    {
    public:
        RenderManager(Application& app) : m_application(app) {};
        void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

    private:
        Application& m_application;
    };
};


