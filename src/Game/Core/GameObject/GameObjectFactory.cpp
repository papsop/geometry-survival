#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/View.h>
#include <Engine/Components/Drawables/ShapeDrawableComponent.h>
#include <Engine/Components/Drawables/TextDrawableComponent.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>

#include "../../Components/Actor/ActorComponent.h"
#include "../../Components/Enemy/AIChasePlayerComponent.h"
#include "../../Components/Pickables/ExperienceGlobeComponent.h"
#include "../../Physics/Filters.h"

#include "../../Components/Player/InputComponent.h"
#include "../../Components/Player/LevelComponent.h"
#include "../../Components/Player/PickUpFieldComponent.h"
#include "../../Components/Player/PlayerComponent.h"
#include "../../Components/Actor/WeaponComponent.h"
#include "../../Components/Actor/Weapons.h"
#include "../../Components/Enemy/EnemyComponent.h"
#include "../../Components/Actor/WeaponComponent.h"
#include "../../Components/Actor/BulletComponent.h"
#include "../../Components/View/CombatTextComponent.h"


namespace Game
{

	Engine::GameObject* GameObjectFactory::CreateEnemy(EnemyFactoryDef def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
		physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;

		Engine::ShapeDrawableDef shapeDef;
		shapeDef.Color = sf::Color::Yellow;
		shapeDef.PointCount = 5;
		shapeDef.Radius = 2.f;
		shapeDef.Layer = Engine::view::Layer::ENEMY;

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = shapeDef.Radius;

		RPGActorDef rpgActorDef;
		rpgActorDef.MaxHealth = 10;
		rpgActorDef.MovementSpeed = 10.0f;

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;
		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Enemy by factory", Engine::GameObjectTag::ENEMY, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::ShapeDrawableComponent>(shapeDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<RPGComponent>(rpgActorDef);
		obj->AddComponent<ActorComponent>();
		obj->AddComponent<EnemyComponent>();
		//obj->AddComponent<AIChasePlayerComponent>();
		//obj->AddComponent<ScatterFieldComponent>();

		obj->SetActive(true);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreateExperienceGlobe(ExperienceGlobeDef def)
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

		obj->SetActive(true);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreatePlayerObject(PlayerObjectDef def)
	{
    Engine::ShapeDrawableDef shapeDef;
		shapeDef.Color = sf::Color::Green;
		shapeDef.PointCount = 3;
		shapeDef.Radius = 2.f;
		shapeDef.Layer = Engine::view::Layer::PLAYER;

    Engine::PhysicsBodyDef physBodyDef;
    physBodyDef.BodyType = b2_dynamicBody;
    physBodyDef.CategoryBits = 0x1;
    physBodyDef.MaskBits = 0x1;

		Engine::ITransform::TransformDefinition transformDefDefault; // use default

    Engine::CircleFixtureDef circleFixtureDef;
    circleFixtureDef.Radius = 2.0f;
		

    physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
    physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::PLAYER;
		spriteDef.TexturePath = "assets/sprites/player.png";
		spriteDef.Size = { 4.0f, 4.0f };

    auto* player = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::PLAYER, transformDefDefault);
    player->GetTransform()->SetPosition({ 5.0f, 0.0f });
    player->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
    //player->AddComponent<Engine::ShapeDrawableComponent>(shapeDef);
		player->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		player->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);

    RPGActorDef rpgActorDef;
    rpgActorDef.MaxHealth = 100;
    rpgActorDef.AttackSpeed = 100.0f;
    rpgActorDef.MovementSpeed = 20.0f;
    player->AddComponent<RPGComponent>(rpgActorDef);
    player->AddComponent<ActorComponent>();
    player->AddComponent<PickUpFieldComponent>();
    player->AddComponent<InputComponent>();
    player->AddComponent<WeaponComponent>();
		player->AddComponent<PlayerComponent>();
		player->AddComponent<LevelComponent>();

    auto* weaponComp = player->GetComponent<WeaponComponent>();
    weaponComp->EquipWeapon(std::make_unique<PistolWeapon>());

		player->SetActive(true);
		return player;
	}

	Engine::GameObject* GameObjectFactory::CreateBulletObject(BulletFactoryDef def)
	{
		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;
		transformDef.Rotation = def.Rotation;

		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Bullet", Engine::GameObjectTag::PLAYER_BULLET, transformDef);

		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.IsBullet = true;
		physBodyDef.CategoryBits = physics::EntityCategory::PLAYER_BULLET;
		physBodyDef.MaskBits = physics::EntityMask::M_PLAYER_BULLET;

		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);


		Engine::ShapeViewDef shapeViewDef;
		shapeViewDef.Color = sf::Color::Magenta;
		shapeViewDef.PointCount = 3;
		shapeViewDef.Radius = 0.5f;
		shapeViewDef.Layer = Engine::view::Layer::BULLET;

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = 0.5f;
		circleFixtureDef.IsSensor = true;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::BULLET;
		spriteDef.TexturePath = "assets/sprites/bullet.png";
		//obj->AddComponent<Engine::ShapeViewComponent>(shapeViewDef);
		obj->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);

		BulletDef bulletDef;
		bulletDef.Damage = def.Damage;
		bulletDef.BulletHits = def.BulletHits;
		bulletDef.BurningDamage = def.BurningDamage;
		obj->AddComponent<BulletComponent>(bulletDef);

		obj->SetActive(true);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreateCombatTextObject(CombatTextDef def)
	{
		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;

		auto obj = Engine::GameObjectManager::Get().CreateGameObject("CombatText", Engine::GameObjectTag::UNTAGGED, transformDef);

		Engine::TextDrawableDef textDef;
		textDef.Color = sf::Color::Red;
		textDef.CharacterSize = 16;
		textDef.Value = std::to_string(def.Damage);
		textDef.Layer = Engine::view::Layer::UI;

		obj->AddComponent<Engine::TextDrawableComponent>(textDef);
		obj->AddComponent<CombatTextComponent>(.500f);
		
		obj->SetActive(true);
		return obj;
	}

};