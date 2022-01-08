#pragma once
#include "../Core.h"

namespace Game
{
    class SquareComponent : public IRenderableShapeComponent
    {
    public:
        SquareComponent(GameObject& obj, sf::Color color, int zIndex);
        ~SquareComponent();

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const view::Shape& GetRenderableShape() override;
    private:
        view::Shape m_shape;
    };
};


