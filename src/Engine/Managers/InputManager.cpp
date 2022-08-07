#include "InputManager.h"
#include "../Application.h"

#include <algorithm>
#include <iostream>

namespace Engine
{
    InputManager& InputManager::Get() { return Application::Instance().GetInputManager(); }

    InputManager::InputManager()
        : m_actions()
        , m_axis()
        , m_mapKeyToAction()
        , m_mapMouseToAction()
        , m_mousePosition(0, 0)
        , m_currentCursorInput(InputManager::CursorInput::Mouse)
    {
        // Keyboard
        m_mapKeyToAction[sf::Keyboard::A] = Action::MoveLeft;
        m_mapKeyToAction[sf::Keyboard::D] = Action::MoveRight;
        m_mapKeyToAction[sf::Keyboard::W] = Action::MoveUp;
        m_mapKeyToAction[sf::Keyboard::S] = Action::MoveDown;

        m_mapKeyToAction[sf::Keyboard::Left] = Action::MoveLeft;
        m_mapKeyToAction[sf::Keyboard::Right] = Action::MoveRight;
        m_mapKeyToAction[sf::Keyboard::Up] = Action::MoveUp;
        m_mapKeyToAction[sf::Keyboard::Down] = Action::MoveDown;

        m_mapKeyToAction[sf::Keyboard::Space] = Action::Fire1;
        m_mapKeyToAction[sf::Keyboard::R] = Action::Reload;

        m_mapKeyToAction[sf::Keyboard::Tilde] = Action::ShowConsole;
        m_mapKeyToAction[sf::Keyboard::F9] = Action::ShowDebugDraw;
        m_mapKeyToAction[sf::Keyboard::F7] = Action::TestButton;

        // Mouse
        m_mapMouseToAction[sf::Mouse::Button::Left] = Action::Fire1;

        // Joystick
        // A = 0
        // B = 1
        // X = 2
        // Y = 3
        m_mapJoystickToAction[1] = Action::Fire1;
    }

    InputManager::Action InputManager::GetActionFromKey(sf::Keyboard::Key key)
    {
        if (m_mapKeyToAction.find(key) != m_mapKeyToAction.end())
            return m_mapKeyToAction[key];
        else
            return Action::Unknown;
    }

	InputManager::Action InputManager::GetActionFromMouse(sf::Mouse::Button mouse)
	{
		if (m_mapMouseToAction.find(mouse) != m_mapMouseToAction.end())
			return m_mapMouseToAction[mouse];
		else
			return Action::Unknown;
	}

	InputManager::Action InputManager::GetActionFromJoystick(size_t joystick)
	{
		if (m_mapJoystickToAction.find(joystick) != m_mapJoystickToAction.end())
			return m_mapJoystickToAction[joystick];
		else
			return Action::Unknown;
	}

	math::Vec2 InputManager::GetJoystickMoveAxes(size_t joystickId)
	{
        if (sf::Joystick::isConnected(joystickId))
        {
            return { 
                sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.0f,
                sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100.0f 
            };
        }
        return {0.0f, 0.0f};
	}

	void InputManager::UpdateAction(Action action, bool isPressed)
	{
        if (action == Action::Unknown)
            return;

        auto& entry = m_actions[static_cast<size_t>(action)];
        entry.Pressed = isPressed;

        if (isPressed && !entry.WasPressedLastFrame)
            entry.PressedThisFrame = true;
        else if (!isPressed && entry.WasPressedLastFrame)
            entry.ReleasedThisFrame = true;

        // InputManager::PostUpdate() takes cares of cleaning the entries
	}

    void InputManager::HandleWindowEvent(const sf::Event& event)
    {

        // Keyboard event
        if (event.type == sf::Event::KeyPressed)
        {
            auto action = GetActionFromKey(event.key.code);
            UpdateAction(action, true);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            auto action = GetActionFromKey(event.key.code);
            UpdateAction(action, false);
        }// Mouse event
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            auto action = GetActionFromMouse(event.mouseButton.button);
            UpdateAction(action, true);
        }
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			auto action = GetActionFromMouse(event.mouseButton.button);
            UpdateAction(action, false);
		}
        // joystick event
        else if (event.type == sf::Event::JoystickButtonPressed)
        {
            auto action = GetActionFromJoystick(event.joystickButton.button);
            UpdateAction(action, true);
        }
		else if (event.type == sf::Event::JoystickButtonReleased)
		{
			auto action = GetActionFromJoystick(event.joystickButton.button);
			UpdateAction(action, false);
		}
    }



	void InputManager::Update()
    {
        // mouse position update
        m_mousePosition = ViewManager::Get().GetMousePosition();

        float horizontal = 0;
        float vertical = 0;

        // Axis check
        if (GetAction(Action::MoveLeft).Pressed)
            horizontal -= 1;
        if (GetAction(Action::MoveRight).Pressed)
            horizontal += 1;

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

    sf::Vector2f InputManager::GetCursorPosition()
{
        return m_mousePosition;
    }

};