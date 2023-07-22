#include "GameObjectFactory.h"

#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Components/Physics.h>
#include <Engine/Components/Drawables/ShapeDrawableComponent.h>
#include <Engine/Components/Drawables/TextDrawableComponent.h>
#include <Engine/Components/Drawables/SpriteDrawableComponent.h>
#include <Engine/Components/Drawables/AnimationControllerComponent.h>
#include <Engine/Components/Animations/AnimatorComponent.h>

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
#include "../../Components/Actor/DestroyAfterTimeComponent.h"
#include "../../Components/Enemy/EnemyComponent.h"
#include "../../Components/Actor/WeaponComponent.h"
#include "../../Components/Actor/BulletComponent.h"
#include "../../Components/View/CombatTextComponent.h"
#include "../../Components/Skills/SkillsComponent.h"
#include "../../Components/Skills/BulletDamageSkill.h"

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
		spriteDef.Size = { 18.5f, 17.0f };

		Engine::ITransform::TransformDefinition transformDef;
		transformDef.Position = def.Position;

		EnemyComponentDef enemyDef;
		enemyDef.DamagePerSecond = def.DamagePerSecond;
		// Fixture/PhysicsBody set rotation
		auto obj = Engine::GameObjectManager::Get().CreateGameObject("Enemy by factory", Engine::GameObjectTag::ENEMY, transformDef);
		obj->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
		obj->AddComponent<Engine::AnimatorComponent>();
		obj->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<RPGComponent>(rpgActorDef);
		obj->AddComponent<ActorComponent>();
		obj->AddComponent<EnemyComponent>(enemyDef);

		auto* enemyComponent = obj->GetComponent<EnemyComponent>();

		auto objAnimatorController = std::make_unique<Engine::AnimatorController>();
		auto* moveState = objAnimatorController->AddAnimatorState("enemy_move", true);
		auto* deathState = objAnimatorController->AddAnimatorState("enemy_die", false);
		deathState->OnAnimationFinishedSignal.AddListener(enemyComponent, &EnemyComponent::OnDeathAnimationFinishedCallback);

		objAnimatorController->AddAnyStateTransition(deathState, enemyComponent->IsDying(), Engine::AnimatorTransitionConditionType::EQUALS, true);
		

		obj->GetComponent<Engine::AnimatorComponent>()->SetAnimatorController(std::move(objAnimatorController));

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
		obj->AddComponent<Engine::AnimatorComponent>();

		auto objAnimatorController = std::make_unique<Engine::AnimatorController>();
		auto* idleState = objAnimatorController->AddAnimatorState("experience_rotate", true);

		obj->GetComponent<Engine::AnimatorComponent>()->SetAnimatorController(std::move(objAnimatorController));

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
    circleFixtureDef.Radius = 2.5f;
		
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
		//player->AddComponent<Engine::AnimationControllerComponent>();
		player->AddComponent<Engine::AnimatorComponent>();

    RPGActorDef rpgActorDef;
    rpgActorDef.MaxHealth = 100;
    rpgActorDef.AttackSpeed = 100.0f;
    rpgActorDef.MovementSpeed = 20.0f;
    player->AddComponent<RPGComponent>(rpgActorDef);
    player->AddComponent<ActorComponent>();
    player->AddComponent<PickUpFieldComponent>();
		player->AddComponent<SkillsComponent>();						// Needs to be registered before WeaponComponent
    player->AddComponent<WeaponComponent>();
		player->AddComponent<InputComponent>();
		player->AddComponent<PlayerComponent>();
		player->AddComponent<LevelComponent>();

		std::unique_ptr<ISkill> testSkill = std::make_unique<BulletDamageSkill>();
		player->GetComponent<SkillsComponent>()->AddSkill(std::move(testSkill));
		
		// Animation setup
// 		auto* animController = player->GetComponent<Engine::AnimationControllerComponent>();
// 		auto* idleState = animController->GetStateMachine().AddAnimationState("player_idle");
// 		auto* runState = animController->GetStateMachine().AddAnimationState("player_move");
// 
 		
// 		idleState->AddStateTransition(runState, actor->IsMoving(), Engine::TransitionConditionType::EQUALS, true);
// 		runState->AddStateTransition(idleState, actor->IsMoving(), Engine::TransitionConditionType::EQUALS, false);

		auto playerAnimatorController = std::make_unique<Engine::AnimatorController>();
		auto* idleState = playerAnimatorController->AddAnimatorState("player_idle", true);
		auto* moveState = playerAnimatorController->AddAnimatorState("player_move", true); // test one shot
		
		playerAnimatorController->SetDefaultState(idleState);

		auto* actor = player->GetComponent<ActorComponent>();
		idleState->AddStateTransition(moveState, actor->IsMoving(), Engine::AnimatorTransitionConditionType::EQUALS, true);
		moveState->AddStateTransition(idleState, actor->IsMoving(), Engine::AnimatorTransitionConditionType::EQUALS, false);
		player->GetComponent<Engine::AnimatorComponent>()->SetAnimatorController(std::move(playerAnimatorController));

    auto* weaponComp = player->GetComponent<WeaponComponent>();
    weaponComp->EquipWeapon(std::make_unique<PistolWeapon>());

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
		circleFixtureDef.Radius = 1.0f;
		circleFixtureDef.IsSensor = true;

		Engine::SpriteDrawableDef spriteDef;
		spriteDef.Layer = Engine::view::Layer::BULLET;
		spriteDef.TextureName = "bullet";
		spriteDef.Size = { 6.0f, 6.0f };

		obj->AddComponent<Engine::SpriteDrawableComponent>(spriteDef);
		obj->AddComponent<Engine::CircleFixtureComponent>(circleFixtureDef);
		obj->AddComponent<Engine::AnimationControllerComponent>();
		obj->AddComponent<DestroyAfterTimeComponent>(3.0f);

		auto* animController = obj->GetComponent<Engine::AnimationControllerComponent>();
		auto* flyingState = animController->GetStateMachine().AddAnimationState("bullet_flying");

		BulletDef bulletDef;
		bulletDef.Damage = def.Damage;
		bulletDef.BulletHits = def.BulletHits;
		bulletDef.BurningDamage = def.BurningDamage;
		obj->AddComponent<BulletComponent>(bulletDef);

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

		return obj;
	}

};