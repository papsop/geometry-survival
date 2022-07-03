#include "InputComponent.h"

#include "../Actor/ActorComponent.h"

#include <Engine/Application.h>
#include <Engine/Managers/ViewManager.h>
namespace Game
{
    InputComponent::InputComponent(Engine::GameObject& obj)
        : IComponent(obj)
        , m_inputManager(Engine::InputManager::Get())
    {
        SetRequiredComponents<ActorComponent>();
    }

    void InputComponent::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    InputComponent::~InputComponent()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }

    void InputComponent::Update(float dt)
    {
        auto actorComponent = Owner.GetComponent<ActorComponent>();
        if (actorComponent == nullptr) return;

        // rotation
        auto b2MousePos = Engine::ViewManager::Get().pixelsToCoords(m_inputManager.GetMousePosition());
        float angle = Engine::math::AngleBetweenVecs(Owner.GetTransform().Position, b2MousePos);

        actorComponent->AddCommand<RotateCommand>(angle);
        // movement
        float horizontal = m_inputManager.GetAxis(Engine::InputManager::Axis::Horizontal);
        float vertical = -m_inputManager.GetAxis(Engine::InputManager::Axis::Vertical);

        actorComponent->AddCommand<MoveCommand>(horizontal, vertical);
        
        // shooting
        if (m_inputManager.GetAction(Engine::InputManager::Action::Fire1).Pressed)
            actorComponent->AddCommand<FireCommand>();
    }
};