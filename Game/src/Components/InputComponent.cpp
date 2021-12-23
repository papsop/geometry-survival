#include "InputComponent.h"
#include "../Components/Commands.h"
#include "../Application.h"

#include <iostream>
namespace Game
{
    InputComponent::InputComponent(GameObject& obj)
        : IComponent(obj)
        , m_inputManager(Application::Instance().GetInputManager())
    {
    }

    void InputComponent::OnGameObjectChanged()
    {
        m_actorComponent = m_owner.GetComponent<ActorComponent>();
    }

    void InputComponent::Update(float dt)
    {
        float horizontal = m_inputManager.GetAxis(InputManager::Axis::Horizontal);
        float vertical = m_inputManager.GetAxis(InputManager::Axis::Vertical);
        
        if (auto tmp = m_actorComponent.lock())
        {
            tmp->AddCommand(MoveCommand(horizontal, vertical));
        }
    }

};