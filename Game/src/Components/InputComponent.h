#pragma once
#include "IComponent.h"
#include "ActorComponent.h"
#include "../Singletons/InputManager.h"

namespace Game
{
    class GameObject;

    class InputComponent : public IComponent
    {
    public:
        InputComponent(GameObject& obj);
        ~InputComponent() override = default;

        void Update(float dt) override;
        void OnGameObjectChanged() override;

    private:
        InputManager& m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;


    };
};


