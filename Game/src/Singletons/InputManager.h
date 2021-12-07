 #pragma once
#include <SFML/Window.hpp>
#include <array>

#include "../Application.h"

namespace Game {
    class InputManager
    {
    public:
        InputManager(Application& app) 
            : m_application(app)
            , m_keys() {};
        ~InputManager() = default;

        const bool IsKeyPressed(sf::Keyboard::Key key) const { return m_keys[key]; };
        sf::Vector2f GetMousePos();
    private:
        Application& m_application;

        void KeyPressed(sf::Keyboard::Key key) { m_keys[key] = true; }
        void KeyReleased(sf::Keyboard::Key key) { m_keys[key] = false; }

        std::array<bool, sf::Keyboard::Key::KeyCount> m_keys;

    friend class Application;
    };
};
