#pragma once
#include "IComponent.h"
#include "SFML/System/Vector2.hpp"

namespace Game
{
    class RenderComponent : public IComponent
    {
    public:
        RenderComponent(){};

        ~RenderComponent() override;

        void Update(float dt) override;

        void Render() {};
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_scale;
    };
};

