#pragma once
#include "../IComponent.h"
#include <memory>

namespace Game
{
    class GameObject;

    class TriangleComponent : public IRenderableComponent
    {
    public:
        TriangleComponent(GameObject& obj, int zIndex);
        ~TriangleComponent() override = default;

        void Init() override;
        void Render() override;
    private:
        std::weak_ptr<RenderManager> m_renderManager;

        std::shared_ptr<sf::CircleShape> m_shape;
    };

};

