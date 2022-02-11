#pragma once
#include "../Subsystems/ViewSubsystem.h"

#include <SFML/Window.hpp>
#include <array>
#include <unordered_map>

namespace Engine {

    class Application;
    class InputComponent;

    class InputManager
    {
    public:
        enum class Axis
        {
            Unknown,
            Horizontal,
            Vertical
        };

        enum class Action
        {
            Unknown,
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            Fire1,
            Fire2,
            Use,
            ShowConsole,

            // always last
            NumberOfActions
        };
        struct ActionEntry
        {
            bool Pressed = false;
            bool PressedThisFrame = false;
            bool ReleasedThisFrame = false;
            bool WasPressedLastFrame = false;
        };
        ~InputManager() = default;

        static InputManager& Get();

        float GetAxis(Axis axis);
        const ActionEntry& GetAction(Action action);

        sf::Vector2i GetMousePosition();

    private:
        InputManager();

        Action GetActionFromKey(sf::Keyboard::Key);
        void HandleWindowEvent(const sf::Event& event);
        void Update();
        void PostUpdate();

        void SetViewSubsystem(ViewSubsystem* viewSubsystem);

        std::array<float, 3> m_axis;

        std::array<ActionEntry, static_cast<size_t>(Action::NumberOfActions)> m_actions;

        std::unordered_map<sf::Keyboard::Key, Action> m_mapKeyToAction;
        sf::Vector2i m_mousePosition;

        ViewSubsystem* m_viewSubsystem = nullptr;

    friend class ViewSubsystem; // needs to communicate about MousePos
    friend class Application;   // only Application can create a manager
    };
};
