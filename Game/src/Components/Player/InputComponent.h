#pragma once
#include "../Core.h"
#include "../Actor.h"
#include "../../Managers/InputManager.h"

namespace Game
{
    class GameObject;

    class InputComponent : public IComponent
    {
    public:
        InputComponent(GameObject& obj);
        ~InputComponent() override;

        void Update(float dt) override;
        void OnGameObjectChanged() override;

    private:
        InputManager& m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;
    };
};


