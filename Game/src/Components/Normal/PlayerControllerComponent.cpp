#include "PlayerControllerComponent.h"

#include "../../GameObject.h"
#include "../../Application.h"

namespace Game
{
    PlayerControllerComponent::PlayerControllerComponent(GameObject &obj) 
        : IComponent(obj)
        , m_inputManager(Application::Instance().GetInputManager())
    {
    }

    void PlayerControllerComponent::OnGameObjectChanged()
    {
        m_actorComponent = m_owner.GetComponent<ActorComponent>();
    }

    void PlayerControllerComponent::Update(float dt)
    {

        // keyboard
        sf::Vector2f movement(0.0f, 0.0f);

        if (m_inputManager.IsKeyPressed(sf::Keyboard::Key::W))
            movement.y -= dt;
        if (m_inputManager.IsKeyPressed(sf::Keyboard::Key::S))
            movement.y += dt;
        if (m_inputManager.IsKeyPressed(sf::Keyboard::Key::A))
            movement.x -= dt;
        if (m_inputManager.IsKeyPressed(sf::Keyboard::Key::D))
            movement.x += dt;

        // normalize myself since the library doesnt include it zZz
        float movementVecLength = sqrt(movement.x * movement.x + movement.y * movement.y);
        if (movementVecLength != 0)
            movement /= movementVecLength;

        if (auto tmp = m_actorComponent.lock())
        {
            tmp->RotateTo(m_inputManager.GetMousePos());
            tmp->SetMovementVector(movement);
        }
        else
        {
            // LOG no component
        }
    }
};