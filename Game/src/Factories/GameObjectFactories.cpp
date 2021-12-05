#include "GameObjectFactories.h"
#include "../Components/Renderable/SquareComponent.h"
#include "../Components/Renderable/TriangleComponent.h"
#include "../Components/Normal/ActorComponent.h"
#include "../Components/Normal/PlayerControllerComponent.h"
#include "../Components/Normal/RigidbodyComponent.h"
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
        obj->AddComponent<TriangleComponent>(TriangleComponent(*obj, 1));
        obj->AddComponent<SquareComponent>(SquareComponent(*obj, 0));

        // todo: obj->AddComponent<SquareComponent>(*obj, 0);
        obj->InitAllComponents();
        return obj;
    }
    // /PlayerFactory
};