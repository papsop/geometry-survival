set(ACTOR_SOURCE
	Actor/ActorComponent.h
	Actor/ActorComponent.inl
	Actor/ActorComponent.cpp
	Actor/BulletComponent.h
	Actor/BulletComponent.cpp
	Actor/Commands.h
	Actor/Commands.cpp
	Actor/RPGComponent.h
	Actor/RPGComponent.cpp
	Actor/IBulletMiddleware.h
	Actor/WeaponComponent.h
	Actor/WeaponComponent.cpp
	Actor/DestroyAfterTimeComponent.h
	Actor/DestroyAfterTimeComponent.cpp
	
	Actor/Weapons.h
)

set(PLAYER_SOURCE
	Player/PlayerComponent.h
	Player/PlayerComponent.cpp
	Player/Inputcomponent.h
	Player/Inputcomponent.cpp
	Player/PickUpFieldComponent.h
	Player/PickUpFieldComponent.cpp
	Player/LevelComponent.h
	Player/LevelComponent.cpp
	Player/PlayerSpawnerComponent.h
	Player/PlayerSpawnerComponent.cpp
)

set(ENEMY_SOURCE
	Enemy/EnemyComponent.h
	Enemy/EnemyComponent.cpp
	Enemy/AIChasePlayerComponent.h
	Enemy/AIChasePlayerComponent.cpp
	Enemy/EnemySpawnerComponent.h
	Enemy/EnemySpawnerComponent.cpp

	Enemy/States/ChaseTargetState.h
	Enemy/States/ChaseTargetState.cpp
	Enemy/States/EnemyStunnedState.h
	Enemy/States/EnemyStunnedState.cpp
)

set(STATES_SOURCE
	States/Actor.h
	States/Actor/Actor_ChasePlayer.h
	States/Actor/Actor_ChasePlayer.cpp
	States/Actor/Actor_Stunned.h
	States/Actor/Actor_Stunned.cpp
)

set(PICKABLES_SOURCE
	Pickables/ExperienceGlobeComponent.h
	Pickables/ExperienceGlobeComponent.cpp
	Pickables/PickableItemComponent.h
	Pickables/PickableItemComponent.cpp
)

set(UI_SOURCE
	UI/MainMenuScreenComponent.h
	UI/MainMenuScreenComponent.cpp
	UI/SplashScreenComponent.h
	UI/SplashScreenComponent.cpp
	UI/IngameMenuComponent.h
	UI/IngameMenuComponent.cpp
	UI/IngameHUDComponent.h
	UI/IngameHUDComponent.cpp
	UI/SettingsScreenComponent.h
	UI/SettingsScreenComponent.cpp
	UI/SkillPickerScreenComponent.h
	UI/SkillPickerScreenComponent.cpp
	UI/GameOverMenuComponent.h
	UI/GameOverMenuComponent.cpp
	UI/IngameCrosshairComponent.h
	UI/IngameCrosshairComponent.cpp

	UI/Controllers/IngameUIControllerComponent.h
	UI/Controllers/IngameUIControllerComponent.cpp
	UI/Controllers/MainMenuUIControllerComponent.h
	UI/Controllers/MainMenuUIControllerComponent.cpp
)

set(VIEW_SOURCE
	View/CameraComponent.h
	View/CameraComponent.cpp
	View/CombatTextComponent.h
	View/CombatTextComponent.cpp
	View/BackgroundComponent.h
	View/BackgroundComponent.cpp
)

set(SKILLS_SOURCE
	Skills/ISkill.h
	Skills/SkillsComponent.h
	Skills/SkillsComponent.cpp
	Skills/BulletSizeSkill.h
	Skills/BulletSizeSkill.cpp
	Skills/BulletDamageSkill.h
	Skills/BulletDamageSkill.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${ACTOR_SOURCE}
	${PLAYER_SOURCE}
	${ENEMY_SOURCE}
	${STATES_SOURCE}
	${PICKABLES_SOURCE}
	${UI_SOURCE}
	${VIEW_SOURCE}
	${SKILLS_SOURCE}
)