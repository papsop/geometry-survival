#include "InputManager.h"

namespace Game
{
    sf::Vector2f InputManager::GetMousePos()
    {
        return sf::Vector2f(m_application.GetMousePosition());
    }
};