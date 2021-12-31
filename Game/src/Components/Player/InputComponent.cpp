#include "InputComponent.h"
#include "../../Application.h"
#include "../../Utils/VectorUtils.h"

#include <iostream>
namespace Game
{
    InputComponent::InputComponent(GameObject& obj)
        : IComponent(obj)
        , m_inputManager(Application::Instance().GetInputManager())
    {
        Application::Instance().GetSubsystemManager().m_actor->RegisterComponent(this);
    }

    InputComponent::~InputComponent()
    {
        Application::Instance().GetSubsystemManager().m_actor->UnregisterComponent(this);
    }

    void InputComponent::OnGameObjectChanged()
    {
        m_actorComponent = Owner.GetComponent<ActorComponent>();
    }

    void InputComponent::Update(float dt)
    {
        // rotation
        auto cursorPos = static_cast<sf::Vector2f>(m_inputManager.GetMousePosition());
        auto dirToCursor = Owner.GetTransform().Position - cursorPos;
        
        float angle = RAD_TO_DEG(atan2(dirToCursor.y, dirToCursor.x));
        
        if (auto tmp = m_actorComponent.lock())
        {
            tmp->AddCommand(std::make_unique<RotateCommand>(angle));
        }

        // movement
        float horizontal = m_inputManager.GetAxis(InputManager::Axis::Horizontal);
        float vertical = m_inputManager.GetAxis(InputManager::Axis::Vertical);

        if (auto tmp = m_actorComponent.lock())
        {
            tmp->AddCommand(std::make_unique<MoveCommand>(horizontal, vertical));
        }
    }

};