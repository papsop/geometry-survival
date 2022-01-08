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
        float angle = math::AngleBetweenVecs(Owner.GetTransform().Position, static_cast<sf::Vector2f>(m_inputManager.GetMousePosition()));

        if (auto tmp = m_actorComponent.lock())
        {
            tmp->AddCommand(std::make_unique<RotateCommand>(angle));
        }

        // movement
        float horizontal = m_inputManager.GetAxis(InputManager::Axis::Horizontal);
        float vertical = m_inputManager.GetAxis(InputManager::Axis::Vertical);

        if (m_previousUpdateHorizontal != horizontal || m_previousUpdateVertical != vertical )
        {
            if (auto tmp = m_actorComponent.lock())
            {
                tmp->AddCommand(std::make_unique<MoveCommand>(horizontal, vertical));
                m_previousUpdateHorizontal = horizontal;
                m_previousUpdateVertical = vertical;
            }
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