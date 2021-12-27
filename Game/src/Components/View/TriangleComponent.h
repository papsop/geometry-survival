#pragma once
#include <SFML/Graphics.hpp>
#include "../Core.h"

namespace Game
{
    class TriangleComponent : public IComponent, public IRenderableShape
    {
    public:
        TriangleComponent(GameObject& obj, sf::Color color);
        ~TriangleComponent() = default;

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const view::Shape& GetRenderableShape() override;

    private:
        view::Shape m_shape;
        Transform& m_ownerTransform;
    };
};


