#pragma once
#include "IComponent.h"
#include "SFML/System/Vector2.hpp"

namespace Game 
{
    class GameObject;

    class TransformComponent : public IComponent
    {
    public:
        TransformComponent(GameObject &obj, sf::Vector2f pos, sf::Vector2f scale) 
            : IComponent(obj)
            , m_position(pos)
            , m_scale(scale) 
        {};

        ~TransformComponent() override = default;

        void Update(float dt) override;

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_scale;
    };
};

 