#include "RenderManager.h"
#include "../Application.h"
#include <algorithm>
#include <iostream>

namespace Game
{
    RenderManager::RenderManager(Application& app) 
        : m_application(app) 
    {
    }

    void RenderManager::RequestRender(int zIndex, sf::Drawable *shape)
    {
        m_renderQueue.emplace_back(std::make_pair(zIndex, shape));
    }

    void RenderManager::RenderAll()
    {
        std::sort(m_renderQueue.begin(), m_renderQueue.end(), RenderPairCompare);

        for (auto renderPair : m_renderQueue)
        {
            m_application.Draw(*renderPair.second);
        }
        m_renderQueue.clear();
    }
};