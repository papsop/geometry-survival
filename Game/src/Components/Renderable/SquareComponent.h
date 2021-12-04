#pragma once
#include "../IComponent.h"
#include "../Normal/TransformComponent.h"
#include <memory>

namespace Game 
{
    class GameObject;

    class SquareComponent : public IRenderableComponent
    {
    public:
        SquareComponent(GameObject& obj, int zIndex);
        ~SquareComponent() override = default;

        void Init() override;
        void Render() override;
    private:
        std::shared_ptr<RenderManager> m_renderManager;
        std::weak_ptr<TransformComponent> m_transformComponent;

        std::shared_ptr<sf::CircleShape> m_shape;
    };

};

