#pragma once
#include "../Core.h"

namespace Game
{
    class BoxCollider : public IComponent, public IRenderableShape
    {
    public:
        BoxCollider(GameObject &obj);
        ~BoxCollider() override = default;

        void OnGameObjectChanged() {};
        void Update(float dt) {};
    private:
        Transform& m_ownerTransform;
    };
};
