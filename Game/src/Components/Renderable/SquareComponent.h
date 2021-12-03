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
        SquareComponent(GameObject& obj);
        ~SquareComponent() override = default;

        void Render() override;
    private:
        std::shared_ptr<RenderManager> m_renderManager;
        std::weak_ptr<TransformComponent> m_transformComponent;
    };

};

