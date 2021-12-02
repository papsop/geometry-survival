#pragma once
#include "IComponent.h"
#include "../Singletons/SingletonManager.h"
#include <memory>


namespace Game 
{
    class GameObject;

    class SpriteComponent : public IRenderableComponent
    {
    public:
        SpriteComponent(GameObject &obj);
        ~SpriteComponent() override = default;

        void Render() override;
    private:
        std::shared_ptr<RenderManager> m_renderManager;
    };

};

