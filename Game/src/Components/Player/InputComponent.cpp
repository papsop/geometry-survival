#include "InputComponent.h"
#include "../../Application.h"

#include <iostream>
namespace Game
{
    InputComponent::InputComponent(GameObject& obj)
        : IComponent(obj)
        , m_inputManager(Application::Instance().GetInputManager())
    {
        ACTORSUBSYSTEM_REGISTER(this);
    }

    InputComponent::~InputComponent()
    {
        ACTORSUBSYSTEM_UNREGISTER(this);
    }

    void InputComponent::OnGameObjectChanged()
    {
        m_actorComponent = Owner.GetComponent<ActorComponent>();
    }

    void InputComponent::Update(float dt)
    {
        // rotation
        auto cursorPos = static_cast<sf::Vector2f>(m_inputManager.GetMousePosition());
        auto dirToCursor = cursorPos - Owner.GetTransform().Position;
        
        float angle = -math::RAD_TO_DEG(atan2(dirToCursor.y, dirToCursor.x));
        if (angle < 0)
            angle += 360.0f;

        LOG_INFO("Angle: %f", angle);
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

        // shooting
        if(m_inputManager.GetAction(InputManager::Action::Fire1))
            if (auto tmp = m_actorComponent.lock())
            {
                tmp->AddCommand(std::make_unique<FireCommand>());
            }
    }

    void InputComponent::DebugDraw(view::IViewStrategy* viewStrategy)
    {
        // rotation
        auto cursorPos = static_cast<sf::Vector2f>(m_inputManager.GetMousePosition());
        auto dirToCursor = cursorPos - Owner.GetTransform().Position;

        view::Line line;
        line.Points[0] = sf::Vertex(Owner.GetTransform().Position);
        line.Points[1] = sf::Vertex(Owner.GetTransform().Position + (dirToCursor * 100.0f));
        //line.Points[1] = sf::Vertex(cursorPos)

       // viewStrategy->Render(line);
    }

};