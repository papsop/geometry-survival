#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/View/Renderables.h>
#include <Engine/Core/GameObject.h>

namespace Game
{
    class SplashTitle : public Engine::IRenderableTextComponent
    {
    public:
        SplashTitle(Engine::GameObject& obj);
        ~SplashTitle() override;

        void OnCreate() override;
        void Update(float dt) override {};

        const Engine::view::Text& GetRenderableText() override { return m_text; };
    private:
        Engine::view::Text m_text;
    };
}


