#pragma once
#include "../Core.h"

namespace Game
{
    class FpsCounterComponent : public IRenderableTextComponent
    {
    public:
        FpsCounterComponent(GameObject& obj);
        ~FpsCounterComponent();

        void OnGameObjectChanged() override {};
        void Update(float dt) override;

        const view::Text& GetRenderableText() override;
    private:
        view::Text m_text;
    };
};