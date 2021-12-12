#include "InputManager.h"
#include "../Application.h"

namespace Game
{
    InputManager::InputManager(Application& app)
        : m_application(app)
        , m_keys() 
    {
    };

    sf::Vector2f InputManager::GetMousePos()
    {
        return sf::Vector2f(m_application.GetMousePosition());
    }
};