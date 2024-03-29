#pragma once
#include "IManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "../Core/Events.h"


#include <SFML/Window.hpp>
#include <array>
#include <unordered_map>

namespace Engine {

    class Application;
    class InputComponent;

    class InputManager : public IManager, public IEventListener<event::E_SFMLEvent>
    {
    public:
      // ========================================================
      // Class helpers
      // ========================================================
      enum class CursorInput
      {
          Unknown,
          Mouse,
          Joystick
      };

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
          Reload,
          Use,
          ShowConsole,
          ShowDebugDraw,
          TestButton,
          PauseGame,
          Escape,

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

      // ========================================================
      // Class members
      // ========================================================

      ~InputManager() = default;

      static InputManager& Get();

      float GetAxis(Axis axis);
      const ActionEntry& GetAction(Action action);

      sf::Vector2f GetCursorPosition();

    protected:
		  void ReceiveEvent(const event::E_SFMLEvent& eventData) override;

      void VirtualOnInit() override;
      void VirtualOnDestroy() override;
    private:
      InputManager();

      Action GetActionFromKey(sf::Keyboard::Key key);
      Action GetActionFromMouse(sf::Mouse::Button mouse);
      Action GetActionFromJoystick(size_t joystick);

      math::Vec2 GetJoystickMoveAxes(size_t joystickId);

      void Update();
      void PostUpdate();
      void UpdateAction(Action action, bool isPressed);

      void HandleEscapeAction();
      void HandleShowDebugAction();
      void HandleShowConsolePressed();

      std::array<float, 3> m_axis;

      std::array<ActionEntry, static_cast<size_t>(Action::NumberOfActions)> m_actions;

      std::unordered_map<sf::Keyboard::Key, Action> m_mapKeyToAction;
      std::unordered_map<sf::Mouse::Button, Action> m_mapMouseToAction;
      std::unordered_map<size_t, Action> m_mapJoystickToAction;
      sf::Vector2f m_mousePosition;

      // Default is mouse, but when a player uses joystick, this should swap to Joystick and vice-versa
      CursorInput m_currentCursorInput;
      RenderManager* m_renderManager;

    friend class RenderManager; // needs to communicate about MousePos
    friend class Application;   // only Application can create a manager
    };
};
