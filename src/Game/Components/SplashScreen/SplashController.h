#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/View/Renderables.h>
#include <Engine/Core/GameObject.h>

namespace Game
{
    class SplashController : public Engine::IComponent
    {
    public:
        SplashController(Engine::GameObject& obj);
        ~SplashController() override;

        void OnGameObjectChanged() override {};
        void Update(float dt) override;

    private:
        sf::Vector2f GetRandomPositionOutsideWindow();
        sf::Vector2f GetRandomPositionInsideWindow();
        sf::Color GetRandomColor();

        float m_lastTriangleSpawned = 0.0f;
        const float m_triangleSpawnCooldown = 0.1f;
        int m_triangleZIndex = 10001;
    };
}


