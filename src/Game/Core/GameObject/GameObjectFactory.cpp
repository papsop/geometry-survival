#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/Drawables/ShapeDrawableComponent.h>
#include <Engine/Components/Drawables/TextDrawableComponent.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Components/Drawables/AnimationControllerComponent.h>

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

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = 2.0f;

		RPGActorDef rpgActorDef;
		rpgActorDef.MaxHealth = def.MaxHealth;
		rpgActorDef.MovementSpeed = def.MovementSpeed;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::ENEMY;
		spriteDef.TextureName = "enemy1";
		spriteDef.Size = { 4.0f, 4.0f };
		spriteDef.Color = def.Color;

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;

		EnemyComponentDef enemyDef;
		enemyDef.DamagePerSecond = def.DamagePerSecond;
		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Enemy by factory", Engine::GameObjectTag::ENEMY, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<RPGComponent>(rpgActorDef);
		obj->AddComponent<ActorComponent>();
		obj->AddComponent<EnemyComponent>(enemyDef);

		obj->SetActive(true);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreateExperienceGlobe(ExperienceGlobeDef def)
	{
		Engine::PhysicsBodyDef physBodyDef;
		physBodyDef.BodyType = b2_dynamicBody;
		physBodyDef.CategoryBits = physics::EntityCategory::PICKABLE;
		physBodyDef.MaskBits = physics::EntityMask::M_PICKABLE;

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = .5;
		circleFixtureDef.IsSensor = true;

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::EXPERIENCE_GLOBE;
		spriteDef.TextureName = "experience";
		spriteDef.Size = { 2.0f, 2.0f };

		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Experience globe by factory", Engine::GameObjectTag::EXPERIENCE_GLOBE, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<ExperienceGlobeComponent>();

		obj->SetActive(true);
		return obj;
	}

	Engine::GameObject* GameObjectFactory::CreatePlayerObject(PlayerObjectDef def)
	{
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
		spriteDef.TextureName = "player";
		spriteDef.Size = { 32.0f, 16.0f };

    auto* player = Engine::GameObjectManager::Get().CreateGameObject("Player", Engine::GameObjectTag::PLAYER, transformDefDefault);
    player->GetTransform()->SetPosition({ 5.0f, 0.0f });
    player->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		player->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		player->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		player->AddComponent<Engine::AnimationControllerComponent>();

		player->GetComponent<Engine::AnimationControllerComponent>()->AddAnimationClip("player_idle");
		
    RPGActorDef rpgActorDef;
    rpgActorDef.MaxHealth = 100;
    rpgActorDef.AttackSpeed = 100.0f;
    rpgActorDef.MovementSpeed = 20.0f;
    player->AddComponent<RPGComponent>(rpgActorDef);
    player->AddComponent<ActorComponent>();
    player->AddComponent<PickUpFieldComponent>();
    player->AddComponent<WeaponComponent>();
		player->AddComponent<InputComponent>();
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

		Engine::CircleFixtureDef circleFixtureDef;
		circleFixtureDef.Radius = 0.5f;
		circleFixtureDef.IsSensor = true;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::BULLET;
		spriteDef.TextureName = "bullet";
		spriteDef.Size = { 2.0f, 2.0f };

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