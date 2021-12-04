#pragma once
#include "../IComponent.h"
#include "../Normal/ActorComponent.h"
#include <memory>

namespace Game
{
    class PlayerControllerComponent : public IComponent
    {
    public:
        PlayerControllerComponent(GameObject& obj);
        ~PlayerControllerComponent() override = default;
        
        void Init() override;
        void Update(float dt) override;
    private:
        std::shared_ptr<InputManager> m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;
    };
};


