#pragma once
#include "../Core.h"

namespace Game
{
    class BoxCollider : public IRenderableShapeComponent
    {
    public:
        BoxCollider(GameObject &obj);
        ~BoxCollider() override = default;

        void OnGameObjectChanged() {};
        void Update(float dt) {};

        const view::Shape& GetRenderableShape() override;
    private:
        view::Shape m_shape;
    };
};
