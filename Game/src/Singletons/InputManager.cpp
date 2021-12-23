#include "InputManager.h"
#include "../Application.h"
#include "../Components/InputComponent.h"

#include <algorithm>
#include <iostream>

namespace Game
{

    InputManager::InputManager()
    {
        // TODO own config file
        m_mapKeyToAction[sf::Keyboard::A] = Action::MoveLeft;
        m_mapKeyToAction[sf::Keyboard::D] = Action::MoveRight;
        m_mapKeyToAction[sf::Keyboard::W] = Action::MoveUp;
        m_mapKeyToAction[sf::Keyboard::S] = Action::MoveDown;

        m_mapKeyToAction[sf::Keyboard::Left] = Action::MoveLeft;
        m_mapKeyToAction[sf::Keyboard::Right] = Action::MoveRight;
        m_mapKeyToAction[sf::Keyboard::Up] = Action::MoveUp;
        m_mapKeyToAction[sf::Keyboard::Down] = Action::MoveDown;
    }

    InputManager::Action InputManager::GetActionFromKey(sf::Keyboard::Key key)
    {
        if (m_mapKeyToAction.find(key) != m_mapKeyToAction.end())
            return m_mapKeyToAction[key];
        else
            return Action::Unknown;
    }

    void InputManager::HandleWindowEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            auto action = GetActionFromKey(event.key.code);
            if (action != Action::Unknown)
            {
                m_actions[static_cast<size_t>(action)] = true;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            auto action = GetActionFromKey(event.key.code);
            if (action != Action::Unknown)
            {
                m_actions[static_cast<size_t>(action)] = false;
            }
        }
    }

    void InputManager::Update()
    {
        // Axis check
        float horizontal = 0;
        if (GetAction(Action::MoveLeft))
            horizontal -= 1;
        if (GetAction(Action::MoveRight))
            horizontal += 1;

        float vertical = 0;
        if (GetAction(Action::MoveUp))
            vertical -= 1;
        if (GetAction(Action::MoveDown))
            vertical += 1;

        m_axis[static_cast<size_t>(Axis::Horizontal)] = horizontal;
        m_axis[static_cast<size_t>(Axis::Vertical)] = vertical;
    }


    // Public
    float InputManager::GetAxis(Axis axis)
    {
        return m_axis[static_cast<size_t>(axis)];
    }
    
    bool InputManager::GetAction(Action action)
    {
        return m_actions[static_cast<size_t>(action)];
    }
};