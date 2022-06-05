#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/View.h>

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

};