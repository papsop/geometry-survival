#include "GameObjectFactories.h"
#include "../Components/AllComponents.h"
#include "../Core/Scene.h"
#include "../Application.h"

namespace Game
{

    // PlayerFactory impl
    uint32_t PlayerFactory::CreateGameObject() const
    {
        auto obj = Application::Instance().GetEntityManager().CreateEntityReturnEntity();
        uint32_t objID = 0;
        if (auto tmp = obj.lock())
        {
            objID = tmp->ID;
            tmp->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
            tmp->AddComponent<SquareComponent>(*tmp, sf::Color::Magenta);
            tmp->AddComponent<RigidbodyComponent>(*tmp);
            tmp->AddComponent<TriangleComponent>(*tmp, sf::Color::Black);
            tmp->AddComponent<ActorComponent>(*tmp);
            tmp->AddComponent<InputComponent>(*tmp);
            tmp->AddComponent<DebugNameComponent>(*tmp);
            return tmp->ID;
        }
        assert(false && "Error creating an entity");
    }
    // /PlayerFactory

    // RotatingEnemyFactory impl
    uint32_t SeekingEnemyFactory::CreateGameObject() const
    {
        //auto obj = std::make_shared<GameObject>(1, "SeekingEnemy");
        //obj->GetTransform().Position = sf::Vector2f(400.0f, 400.0f);
        //obj->AddComponent<RigidbodyComponent>(*obj);
        //obj->AddComponent<ActorComponent>(*obj);
        ////obj->AddComponent<SeekingEnemyController>(*obj);
        ////obj->AddComponent<TriangleComponent>(*obj, 1);
        ////obj->AddComponent<SquareComponent>(*obj, 0);

        //return obj;
        return 0;
    }
    // /RotatingEnemyFactory

};