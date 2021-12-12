#pragma once
#include "SFML/Graphics.hpp"
#include <queue>
#include <iostream>

namespace Game
{
    class Application;
    typedef std::pair<int, sf::Drawable*> RenderPair;

    class RenderManager
    {
    public:
        ~RenderManager() = default;
        void RequestRender(int zIndex, sf::Drawable *shape);
        // other
        void RenderAll();
    private:
        RenderManager(Application& app);

        Application& m_application;
        static bool RenderPairCompare(const RenderPair& a, const RenderPair& b) { return a.first < b.first; }
        std::vector<RenderPair> m_renderQueue;

    friend class Application;   // only Application can create a manager
    };
};


