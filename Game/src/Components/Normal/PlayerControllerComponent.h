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
        
        void OnGameObjectChanged() override;
        void Update(float dt) override;
    private:
        InputManager& m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;
    };
};


