#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/View/Renderables.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
    class SplashBackground : public Engine::IRenderableShapeComponent
    {
    public:
        SplashBackground(Engine::GameObject& obj);
        ~SplashBackground() override;

        void OnCreate() override;
        void Update(float dt) override {};
    private:
        Engine::view::Shape m_shape;
    };
}


