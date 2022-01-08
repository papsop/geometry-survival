#pragma once
#include "../Core.h"
#include "../Actor.h"
#include "../../Managers/InputManager.h"

namespace Game
{
    class GameObject;

    class InputComponent : public IComponent, public IDebugDrawComponent
    {
    public:
        InputComponent(GameObject& obj);
        ~InputComponent() override;

        void Update(float dt) override;
        void OnGameObjectChanged() override;
        void DebugDraw(view::IViewStrategy* viewStrategy);

    private:
        InputManager& m_inputManager;
        std::weak_ptr<ActorComponent> m_actorComponent;

        float m_previousUpdateHorizontal = 0.0f;
        float m_previousUpdateVertical = 0.0f;
    };
};


