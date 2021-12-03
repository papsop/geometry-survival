#include "GameObjectFactories.h"
#include "../Components/Renderable/SquareComponent.h"
#include "../Components/Renderable/TriangleComponent.h"
#include "../Components/Normal/TransformComponent.h"
#include "../Scene.h"

namespace Game
{

    // PlayerFactory impl
    std::shared_ptr<GameObject> PlayerFactory::CreateGameObject() const
    {
        auto obj = std::make_shared<GameObject>(Scene::GetNewGameObjectID(), "Player");
        obj->AddComponent<TransformComponent>(TransformComponent(*obj, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(1.0f, 1.0f)));
        obj->AddComponent<TriangleComponent>(TriangleComponent(*obj, 0));
        obj->AddComponent<SquareComponent>(SquareComponent(*obj, 1));
        
        return obj;
    }
    // /PlayerFactory
};