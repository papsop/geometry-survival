#include "InputManager.h"
#include "../Application.h"

#include <algorithm>
#include <iostream>

namespace Engine
{
    InputManager& InputManager::Get() { return Application::Instance().GetInputManager(); }

    InputManager::InputManager()
        : m_viewSubsystem(nullptr)
        , m_actions()
        , m_axis()
        , m_mapKeyToAction()
        , m_mousePosition(0, 0)
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

        m_mapKeyToAction[sf::Keyboard::Space] = Action::Fire1;

        m_mapKeyToAction[sf::Keyboard::Tilde] = Action::ShowConsole;
        m_mapKeyToAction[sf::Keyboard::F9] = Action::ShowDebugDraw;
    }

    void InputManager::SetViewSubsystem(ViewSubsystem* viewSubsystem)
    {
        m_viewSubsystem = viewSubsystem;
    }

    InputManager::Action InputManager::GetActionFromKey(sf::Keyboard::Key key)
    {
        if (m_mapKeyToAction.find(key) != m_mapKeyToAction.end())
            return m_mapKeyToAction[key];
        else
            return Action::Unknown;
    }

    void InputManager::HandleWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            auto action = GetActionFromKey(event.key.code);
            if (action != Action::Unknown)
            {
                auto& entry = m_actions[static_cast<size_t>(action)];
                entry.Pressed = true;
                if (!entry.WasPressedLastFrame) entry.PressedThisFrame = true;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            auto action = GetActionFromKey(event.key.code);
            if (action != Action::Unknown)
            {
                auto& entry = m_actions[static_cast<size_t>(action)];
                entry.Pressed = false;
                if (entry.WasPressedLastFrame) entry.ReleasedThisFrame = true;
            }
        }
    }

    void InputManager::Update()
    {
        // mouse position update
        DD_ASSERT(m_viewSubsystem != nullptr, "InputManager doesn't have ViewSubsystem set");
        m_mousePosition = m_viewSubsystem->GetMousePosition();

        // Axis check
        float horizontal = 0;
        if (GetAction(Action::MoveLeft).Pressed)
            horizontal -= 1;
        if (GetAction(Action::MoveRight).Pressed)
            horizontal += 1;

        float vertical = 0;
        if (GetAction(Action::MoveUp).Pressed)
            vertical -= 1;
        if (GetAction(Action::MoveDown).Pressed)
            vertical += 1;

        m_axis[static_cast<size_t>(Axis::Horizontal)] = horizontal;
        m_axis[static_cast<size_t>(Axis::Vertical)] = vertical;
    }

    void InputManager::PostUpdate()
    {
        // update last frame states
        for (auto& entry : m_actions)
        {
            entry.WasPressedLastFrame = entry.Pressed;
            entry.PressedThisFrame = false;
            entry.ReleasedThisFrame = false;
        }
    }

    // Public
    float InputManager::GetAxis(Axis axis)
    {
        return m_axis[static_cast<size_t>(axis)];
    }
    
    const InputManager::ActionEntry& InputManager::GetAction(Action action)
    {
        return m_actions[static_cast<size_t>(action)];
    }

    sf::Vector2i InputManager::GetMousePosition()
    {
        return m_mousePosition;
    }
};