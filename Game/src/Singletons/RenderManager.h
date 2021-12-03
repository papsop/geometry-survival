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

        static bool RenderPairCompare(const RenderPair& a, const RenderPair& b) { return a.first < b.first; }
        std::vector<RenderPair> m_renderQueue;

    friend class Application;
    };
};


