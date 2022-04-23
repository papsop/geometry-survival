#include "InputComponent.h"

#include "../Actor/ActorComponent.h"

#include <Engine/Application.h>

namespace Game
{
    InputComponent::InputComponent(Engine::GameObject& obj)
        : IComponent(obj)
        , m_inputManager(Engine::InputManager::Get())
    {
    }

    void InputComponent::OnCreate()
    {
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }

    InputComponent::~InputComponent()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void InputComponent::Update(float dt)
    {
        auto actorComponent = Owner.GetComponent<ActorComponent>();
        if (actorComponent == nullptr) return;

        // rotation
        float angle = 0;
            //Engine::math::AngleBetweenVecs(Owner.GetTransform().Position, static_cast<sf::Vector2f>(m_inputManager.GetMousePosition()));

        if (m_previousUpdateRotation != angle)
        {
            actorComponent->AddCommand(std::make_unique<RotateCommand>(angle));
            m_previousUpdateRotation = angle;
        }

        // movement
        float horizontal = m_inputManager.GetAxis(Engine::InputManager::Axis::Horizontal);
        float vertical = m_inputManager.GetAxis(Engine::InputManager::Axis::Vertical);

        if (m_previousUpdateHorizontal != horizontal || m_previousUpdateVertical != vertical)
        {
            actorComponent->AddCommand(std::make_unique<MoveCommand>(horizontal, vertical));
            m_previousUpdateHorizontal = horizontal;
            m_previousUpdateVertical = vertical;
        }

        // shooting
        if (m_inputManager.GetAction(Engine::InputManager::Action::Fire1).Pressed)
            actorComponent->AddCommand(std::make_unique<FireCommand>());
    }
};