#pragma once
#include "Components/Core/IComponent.h"
#include "View/Renderables.h"
#include "Core/GameObject.h"

namespace Game
{
    class SplashTitle : public Engine::IRenderableTextComponent
    {
    public:
        SplashTitle(Engine::GameObject& obj);
        ~SplashTitle() override;

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const Engine::view::Text& GetRenderableText() override { return m_text; };
    private:
        Engine::view::Text m_text;
    };
}


