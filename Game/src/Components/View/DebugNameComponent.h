#pragma once
#include <SFML/Graphics.hpp>
#include "../Core.h"

namespace Game
{
    class DebugNameComponent : public IComponent, public IRenderableText
    {
    public:
        DebugNameComponent(GameObject& obj);
        ~DebugNameComponent() = default;

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const view::Text& GetRenderableText() override;

    private:
        view::Text m_renderableText;
        Transform& m_ownerTransform;
    };
};


