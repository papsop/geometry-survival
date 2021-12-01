#pragma once
#include "IComponent.h"
#include "SFML/System/Vector2.hpp"

namespace Game 
{
    class TransformComponent : public IComponent
    {
    public:
        TransformComponent(sf::Vector2f pos, sf::Vector2f scale) 
            : m_position(pos)
            , m_scale(scale) 
        {};

        ~TransformComponent() override;

        void Update(float dt) override;

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_scale;
    };
};

 