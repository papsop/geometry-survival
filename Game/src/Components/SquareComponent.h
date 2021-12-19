#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"
#include "../utils.h"

namespace Game
{
    class SquareComponent : public IComponent, public IRenderableShape
    {
    public:
        SquareComponent(GameObject& obj, sf::Color color);
        ~SquareComponent() = default;

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const view::Shape& GetRenderableShape() override;

    private:
        view::Shape m_shape;
        Transform& m_ownerTransform;
    };
};


