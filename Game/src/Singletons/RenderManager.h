#pragma once
#include "../Application.h"
#include <queue>

namespace Game
{
    class Application;
    typedef std::pair<int, std::weak_ptr<sf::Drawable>> RenderPair;

    class RenderManager
    {
    public:
        RenderManager(Application& app) : m_application(app) {};
        void RequestRender(int zIndex, std::weak_ptr<sf::CircleShape> shape);
        // other

        void RenderAll();

    private:
        Application& m_application;
        //std::priority_queue<RenderRequest, std::vector<RenderRequest>, RenderRequest> m_renderQueue;
        std::vector<RenderPair> m_renderQueue;

    friend class Application;
    };
};


