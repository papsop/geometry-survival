#include "GameObjectFactories.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Scene.h"

namespace Game
{

    // PlayerFactory impl
    std::shared_ptr<GameObject> PlayerFactory::CreateGameObject() const
    {
        auto obj = std::make_shared<GameObject>(Scene::GetNewGameObjectID(), "Player");
        obj->AddComponent<TransformComponent>(TransformComponent(*obj, sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f)));
        obj->AddComponent<SpriteComponent>(SpriteComponent(*obj));
        return obj;
    }
    // /PlayerFactory
};