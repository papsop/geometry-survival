#include "GameObjectFactories.h"
#include "../Components/Renderable/SquareComponent.h"
#include "../Components/Renderable/TriangleComponent.h"
#include "../Components/Normal/ActorComponent.h"
#include "../Components/Normal/PlayerControllerComponent.h"
#include "../Components/Normal/RigidbodyComponent.h"
#include "../Components/Normal/SeekingEnemyController.h"
#include "../Scene.h"

namespace Game
{

    // PlayerFactory impl
    std::shared_ptr<GameObject> PlayerFactory::CreateGameObject() const
    {
        auto obj = std::make_shared<GameObject>(Scene::GetNewGameObjectID(), "Player");
        obj->GetTransform().Position = sf::Vector2f(200.0f, 200.0f);
        obj->AddComponent<ActorComponent>(ActorComponent(*obj));
        obj->AddComponent<PlayerControllerComponent>(PlayerControllerComponent(*obj));
        obj->AddComponent<RigidbodyComponent>(RigidbodyComponent(*obj));
        obj->AddComponent<TriangleComponent>(TriangleComponent(*obj, 2));
        obj->AddComponent<SquareComponent>(SquareComponent(*obj, 1));

        // todo: obj->AddComponent<SquareComponent>(*obj, 0);
        obj->InitAllComponents();
        return obj;
    }
    // /PlayerFactory

    // RotatingEnemyFactory impl
    std::shared_ptr<GameObject> SeekingEnemyFactory::CreateGameObject() const
    {
        auto obj = std::make_shared<GameObject>(Scene::GetNewGameObjectID(), "SeekingEnemy");
        obj->GetTransform().Position = sf::Vector2f(400.0f, 400.0f);
        obj->AddComponent<ActorComponent>(ActorComponent(*obj));
        obj->AddComponent<RigidbodyComponent>(RigidbodyComponent(*obj));
        obj->AddComponent<SeekingEnemyController>(SeekingEnemyController(*obj));
        obj->AddComponent<TriangleComponent>(TriangleComponent(*obj, 1));
        obj->AddComponent<SquareComponent>(SquareComponent(*obj, 0));

        // todo: obj->AddComponent<SquareComponent>(*obj, 0);
        obj->InitAllComponents();
        return obj;
    }
    // /RotatingEnemyFactory

};