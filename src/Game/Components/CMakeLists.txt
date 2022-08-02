set(ACTOR_SOURCE
	Actor/ActorComponent.h
	Actor/ActorComponent.inl
	Actor/ActorComponent.cpp
	Actor/BulletComponent.h
	Actor/BulletComponent.cpp
	Actor/Commands.h
	Actor/Commands.cpp

	Actor/WeaponComponent.h
	Actor/WeaponComponent.cpp

	Actor/Weapons/IWeapon.h
	Actor/Weapons/IWeapon.cpp
	Actor/Weapons/PistolWeapon.h
	Actor/Weapons/PistolWeapon.cpp
)

set(PLAYER_SOURCE
	Player/PlayerComponent.h
	Player/PlayerComponent.cpp
	Player/Inputcomponent.h
	Player/Inputcomponent.cpp
	Player/TestComponent.h
	Player/TestComponent.cpp
	Player/PickUpFieldComponent.h
	Player/PickUpFieldComponent.cpp
)

set(ENEMY_SOURCE
	Enemy/AIChaseTargetComponent.h
	Enemy/AIChaseTargetComponent.cpp
	Enemy/EasyEnemySpawnerComponent.h
	Enemy/EasyEnemySpawnerComponent.cpp
)

set(SPLASH_SOURCE
	SplashScreen/SplashBackground.h
	SplashScreen/SplashBackground.cpp
	SplashScreen/SplashController.h
	SplashScreen/SplashController.cpp
	SplashScreen/SplashShape.h
	SplashScreen/SplashShape.cpp
	SplashScreen/SplashTitle.h
	SplashScreen/SplashTitle.cpp
)

set(STATES_SOURCE
	States/Actor_ChaseTarget.h
	States/Actor_ChaseTarget.cpp
	States/Actor_Stunned.h
	States/Actor_Stunned.cpp

	States/Weapons/WeaponPistol_Shootable.h
	States/Weapons/WeaponPistol_Shootable.cpp
	States/Weapons/Weapon_Cooldown.h
	States/Weapons/Weapon_Cooldown.inl
	States/Weapons/Weapon_Cooldown.cpp
	States/Weapons/Weapon_Reload.h
	States/Weapons/Weapon_Reload.inl
	States/Weapons/Weapon_Reload.cpp
)

set(PICKABLES_SOURCE
	Pickables/ExperienceGlobeComponent.h
	Pickables/ExperienceGlobeComponent.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${ACTOR_SOURCE}
	${PLAYER_SOURCE}
	${ENEMY_SOURCE}
	${STATES_SOURCE}
	${SPLASH_SOURCE}
	${PICKABLES_SOURCE}
)