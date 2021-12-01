#pragma once
#include "IComponent.h"
#include "../Singletons/SingletonManager.h"
#include <SFML/System/Vector2.hpp>

namespace Game
{
    class RenderComponent : public IComponent
    {
    public:
        RenderComponent()
        {
            m_renderManager = SingletonManager::Instance().GetRenderManager();
        };

        ~RenderComponent() override;

        void Update(float dt) override;

        void Render();
    private:
        std::shared_ptr<RenderManager> m_renderManager;
    };
};

