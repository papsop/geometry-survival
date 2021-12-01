#include "RenderManager.h"
#include <iostream>

namespace Game
{
    void RenderManager::Draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_application.Draw(drawable, states);
    }
};