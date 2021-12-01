#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>

#include "../Application.h"

namespace Game {
    class InputManager
    {
    public:
        const bool IsKeyPressed(sf::Keyboard::Key key) const { return m_keys[key]; };

    private:
        void KeyPressed(sf::Keyboard::Key key) { m_keys[key] = true; }
        void KeyReleased(sf::Keyboard::Key key) { m_keys[key] = false; }

        std::array<bool, sf::Keyboard::Key::KeyCount> m_keys;

    friend class Application;
    };
};
