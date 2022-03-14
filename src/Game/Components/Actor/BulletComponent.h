#pragma once
#include <Engine/Components/Core.h>

namespace Game
{
    class BulletComponent : public Engine::IComponent
    {
    public:
        BulletComponent(Engine::GameObject& obj);
        ~BulletComponent();

        void OnCreate() override;
        void Update(float dt) override;
    };
}

