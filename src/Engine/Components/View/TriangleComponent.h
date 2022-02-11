#pragma once
#include "../Core.h"

namespace Engine
{
    class TriangleComponent : public IRenderableShapeComponent
    {
    public:
        TriangleComponent(GameObject& obj, sf::Color color, int zIndex);
        ~TriangleComponent();

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const view::Shape& GetRenderableShape() override;
    private:
        view::Shape m_shape;
    };
};


