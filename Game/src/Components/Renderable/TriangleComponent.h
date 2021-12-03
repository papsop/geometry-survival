#pragma once
#include "../IComponent.h"
#include "../Normal/TransformComponent.h"
#include <memory>

namespace Game
{
    class GameObject;

    class TriangleComponent : public IRenderableComponent
    {
    public:
        TriangleComponent(GameObject& obj, int zIndex);
        ~TriangleComponent() override = default;

        void Render() override;
    private:
        std::shared_ptr<RenderManager> m_renderManager;
        std::weak_ptr<TransformComponent> m_transformComponent;

        std::shared_ptr<sf::CircleShape> m_shape;
    };

};

