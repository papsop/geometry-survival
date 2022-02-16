#pragma once

#include <Engine/Components/Core.h>
#include <Engine/Managers/InputManager.h>

namespace Game
{
    class InputComponent : public Engine::IComponent
    {
    public:
        InputComponent(Engine::GameObject& obj);
        ~InputComponent() override;

        void Update(float dt) override;
        void OnGameObjectChanged() override;

    private:
        Engine::InputManager& m_inputManager;

        float m_previousUpdateHorizontal = 0.0f;
        float m_previousUpdateVertical = 0.0f;
        
        float m_previousUpdateRotation = 0.0f;
    };
};


