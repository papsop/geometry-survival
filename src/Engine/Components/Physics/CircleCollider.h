#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"

namespace Engine
{
    class CircleCollider : public IColliderComponent, public IDebuggable
    {
    public:
        CircleCollider(GameObject& obj);
        ~CircleCollider() override = default;

        void Update(float dt) override;
        void Debug(view::IViewStrategy* viewStrategy);


        void SetRadius(float radius) { m_radius = radius; }
        float GetRadius() const { return m_radius; }
    private:
        float m_radius = 10.0f;
    };
}

