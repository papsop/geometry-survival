#pragma once
#include "Components/Core/IComponent.h"
#include "View/Renderables.h"
#include "Core/GameObject.h"

namespace Game
{
    class SplashBackground : public Engine::IRenderableShapeComponent
    {
    public:
        SplashBackground(Engine::GameObject& obj);
        ~SplashBackground();

        void OnGameObjectChanged() override {};
        void Update(float dt) override {};

        const Engine::view::Shape& GetRenderableShape() override;

    private:
        Engine::view::Shape m_shape;
    };
}


