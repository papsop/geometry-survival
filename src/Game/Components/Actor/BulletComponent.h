#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Managers/PhysicsManager.h>

namespace Game
{
    class BulletComponent : public Engine::IComponent
    {
    public:
        BulletComponent(Engine::GameObject& obj, float damage);
        ~BulletComponent();

        void OnCreate() override;
        void Update(float dt) override;

        void OnCollisionStart(Engine::CollisionData& collision) override;
    private:
        float m_timeToDie = 2.0f;
        float m_damage;
    };
}

