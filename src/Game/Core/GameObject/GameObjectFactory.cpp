#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/View.h>

#include "../../Components/Actor/ActorComponent.h"
#include "../../Components/Enemy/AIChaseTargetComponent.h"
#include "../../Components/Pickables/ExperienceGlobeComponent.h"
#include "../../Physics/Filters.h"

namespace Game
{

	Engine::GameObject* GameObjectFactory::CreateWall(const WallFactoryDef& def)
	{
// 		Engine::PhysicsBodyDef physBodyDef;
// 		physBodyDef.BodyType = b2_staticBody;
// 		physBodyDef.CategoryBits = physics::EntityMask::M_WALL;
// 		physBodyDef.MaskBits = physics::EntityMask::M_WALL;
// 
// 		Engine::RectangleFixtureDef rectangleFixtureDef;
// 		rectangleFixtureDef.Size = def.Size;
// 
// 		Engine::RectangleViewDef rectangleViewDef;
// 		rectangleViewDef.Color = def.Color;
// 		rectangleViewDef.Size = def.Size;
// 
// 		// Fixture/PhysicsBody set rotation
// 		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Wall by factory");
// 		obj->GetTransform()->SetPosition(def.Position);
// 		obj->GetTransform()->SetRotationDeg(def.RotationDeg);
// 		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
// 		obj->AddComponent<Engine::RectangleFixtureComponent>(rectangleFixtureDef);
// 		obj->AddComponent<Engine::RectangleViewComponent>(-1, rectangleViewDef);
// 		return obj;
		return nullptr;
	}


	Engine::GameObject* GameObjectFactory::CreateEnemy(const EnemyFactoryDef& def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
		physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;;

		Engine::ShapeViewDef shapeViewDef;
		shapeViewDef.Color = sf::Color::Red;
		shapeViewDef.PointCount = 5;
		shapeViewDef.Radius = 2.f;
		shapeViewDef.Layer = Engine::view::Layer::ENEMY;

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = shapeViewDef.Radius;

		RPGActorDef rpgActorDef;
		rpgActorDef.MaxHealth = 10;
		rpgActorDef.MovementSpeed = 10.0f;

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;
		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Enemy by factory", Engine::GameObjectTag::ENEMY, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<RPGComponent>(rpgActorDef);
		obj->AddComponent<ActorComponent>();
		obj->AddComponent<AIChaseTargetComponent>(def.Player);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreateExperienceGlobe(const ExperienceGlobeDef& def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.CategoryBits = physics::EntityCategory::PICKABLE;
		physBodyDef.MaskBits = physics::EntityMask::M_PICKABLE;

		Engine::ShapeViewDef shapeViewDef;
		shapeViewDef.Color = sf::Color::White;
		shapeViewDef.PointCount = 10;
		shapeViewDef.Radius = .5;
		shapeViewDef.Layer = Engine::view::Layer::EXPERIENCE_GLOBE;

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = shapeViewDef.Radius;
		circleFixtureDef.IsSensor = true;

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;

		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Experience globe by factory", Engine::GameObjectTag::EXPERIENCE_GLOBE, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<ExperienceGlobeComponent>();
		return obj;
	}

};