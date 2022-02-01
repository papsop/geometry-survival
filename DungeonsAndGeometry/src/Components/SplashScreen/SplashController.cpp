#include "SplashController.h"
#include "Managers/SubsystemManager.h"
#include "Managers/EntityManager.h"

#include "Core/Scene.h"

#include "SplashShape.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

namespace Game
{

    SplashController::SplashController(Engine::GameObject& obj)
        : IComponent(obj)
    {
        srand((unsigned)time(NULL));
        Engine::SubsystemManager::Get().RegisterComponent(this);
    }
    
    SplashController::~SplashController()
    {
        Engine::SubsystemManager::Get().UnregisterComponent(this);
    }

    void SplashController::Update(float dt)
    {
        m_lastTriangleSpawned -= dt;
        if (m_lastTriangleSpawned <= 0.0f)
        {
            auto& scene = Owner.GetScene();

            auto newTriangle = Engine::EntityManager::Get().CreateEntity("SplashShape");
            newTriangle->AddComponent<SplashShape>(rand() % 7 + 3, GetRandomColor(), m_triangleZIndex++);
            newTriangle->GetTransform().Position = GetRandomPositionOutsideWindow();
            newTriangle->GetTransform().Rotation = rand() % 366;

            newTriangle->AddComponent<Engine::RigidbodyComponent>();

            auto dir = GetRandomPositionInsideWindow() - newTriangle->GetTransform().Position;
            newTriangle->GetComponent<Engine::RigidbodyComponent>()->Velocity = dir;
            

            scene.AddGameObject(newTriangle);
            m_lastTriangleSpawned = m_triangleSpawnCooldown;
        }
    }

    // ===============
    // Private helpers
    // ===============

    sf::Vector2f SplashController::GetRandomPositionOutsideWindow()
    {
        float rq = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float chosenX = 0.0f;
        float chosenY = 0.0f;
        // 4 quadrants outside of window
        //    1
        //   +--+
        // 4 |  | 2
        //   +--+
        //    3

        // == 1 ==
        if (rq < 0.25f)
        {
            chosenY = -75.0f;
            // shouldn't be a number, change into config window width etc.. same for next quadrants
            chosenX = static_cast <float> (rand() % 1025);
        }
        // == 2 ==
        else if (rq < 0.5f)
        {
            chosenY = static_cast <float> (rand() % 769);
            chosenX = 1024.0f + 75.0f;
        }
        // == 3 ==
        else if (rq < 0.75f)
        {
            chosenY = 768.0f + 75.0f;
            chosenX = static_cast <float> (rand() % 1025);
        }
        // == 4 ==
        else if (rq <= 1.0f)
        {
            chosenY = static_cast <float> (rand() % 769);
            chosenX = -75.0f;
        }

        return { chosenX, chosenY };
    }

    sf::Vector2f SplashController::GetRandomPositionInsideWindow()
    {
        float chosenX = static_cast <float> (rand() % 1025);
        float chosenY = static_cast <float> (rand() % 769);

        return { chosenX, chosenY };
    }

    sf::Color SplashController::GetRandomColor()
    {
        return sf::Color::Color(rand() % 255, rand() % 255, rand() % 255, 25);
    }

}