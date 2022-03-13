#pragma once
#include "../Core.h"
#include "../../Debug/IDebuggable.h"

namespace Engine
{
    class CircleColliderComponent : public IColliderComponent, public IDebuggable
    {
    public:
        CircleColliderComponent(GameObject& obj, float radius);
        ~CircleColliderComponent() override = default;

        void Update(float dt) override;
        void Debug(view::IViewStrategy* viewStrategy) override;

        ColliderData GetColliderData() override;

        void SetRadius(float radius) { m_radius = radius; }
        float GetRadius() const { return m_radius; }
    private:
        float m_radius = 10.0f;
    };
}

