#pragma once
#include "../Core.h"

namespace Engine
{
    class GameObject;
    class TriangleComponent : public IRenderableShapeComponent
    {
    public:
        TriangleComponent(GameObject& obj, sf::Color color, int zIndex);
        ~TriangleComponent();

        void OnCreate() override;

        void Update(float dt) override 
        {
            m_shape.Color = m_defaultColor;
        }

        void OnCollision(GameObject& other) override;

        const view::Shape& GetRenderableShape() override;
    private:
        view::Shape m_shape;
        sf::Color m_defaultColor;
    };
};


