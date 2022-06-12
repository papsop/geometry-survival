#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/View.h>

#include "../../Components/Actor/ActorComponent.h"
#include "../../Components/Enemy/TestAIComponent.h"

#include "../../Physics/Filters.h"
namespace Game
{

	Engine::GameObject* GameObjectFactory::CreateWall(const WallFactoryDef& def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_staticBody;
		physBodyDef.CategoryBits = physics::EntityMask::M_WALL;
		physBodyDef.MaskBits = physics::EntityMask::M_WALL;

		Engine::RectangleFixtureDef rectangleFixtureDef;
		rectangleFixtureDef.Size = def.Size;

		Engine::RectangleViewDef rectangleViewDef;
		rectangleViewDef.Color = def.Color;
		rectangleViewDef.Size = def.Size;

		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Wall by factory");
		obj->GetTransform().SetPosition(def.Position);
		obj->GetTransform().SetRotationDeg(def.RotationDeg);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::RectangleFixtureComponent>(rectangleFixtureDef);
		obj->AddComponent<Engine::RectangleViewComponent>(Engine::ViewManager::Get().GetZIndexFromPool(), rectangleViewDef);
		return obj;
	}


	Engine::GameObject* GameObjectFactory::CreateEnemy(const EnemyFactoryDef& def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
		physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;;

		Engine::ShapeViewDef shapeViewDef;
		shapeViewDef.Color = sf::Color::Red;
		shapeViewDef.PointCount = 3;
		shapeViewDef.Radius = 2;

		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Enemy by factory");
		obj->GetTransform().SetPosition(def.Position);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(2.0f);
		obj->AddComponent<ActorComponent>(def.MovementSpeed);
		obj->AddComponent<TestAIComponent>(def.Player);
		return obj;
	}

};