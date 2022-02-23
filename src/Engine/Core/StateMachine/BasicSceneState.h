#pragma once
#include "IState.h"

namespace Engine
{
    class BasicSceneState : public ISceneState
    {
    public:
        BasicSceneState(Scene* scene);
        ~BasicSceneState() = default;

        void Enter() override;
        void Update(float dt) override;
        void Exit() override;
    };
}


