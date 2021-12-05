#pragma once
#include "../IComponent.h"
#include "../Normal/ActorComponent.h"
#include <memory>

namespace Game
{
    class PlayerControllerComponent : public IUpdatableComponent
    {
    public:
        PlayerControllerComponent(GameObject& obj);
        ~PlayerControllerComponent() override = default;
        
        void Init() override;
        void Update(float dt) override;
    private:
        std::weak_ptr<InputManager> m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;
    };
};


