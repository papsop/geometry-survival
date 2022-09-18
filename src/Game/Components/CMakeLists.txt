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

	Actor/RPGComponent.h
	Actor/RPGComponent.cpp
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
)

set(ENEMY_SOURCE
	Enemy/AIChaseTargetComponent.h
	Enemy/AIChaseTargetComponent.cpp
	Enemy/EasyEnemySpawnerComponent.h
	Enemy/EasyEnemySpawnerComponent.cpp
)

set(STATES_SOURCE
	States/Actor.h
	States/Actor/Actor_ChaseTarget.h
	States/Actor/Actor_ChaseTarget.cpp
	States/Actor/Actor_Stunned.h
	States/Actor/Actor_Stunned.cpp

	States/Weapons.h
	States/Weapons/WeaponPistol_Shootable.h
	States/Weapons/WeaponPistol_Shootable.cpp
	States/Weapons/Weapon_Reload.h
	States/Weapons/Weapon_Reload.cpp
)

set(PICKABLES_SOURCE
	Pickables/ExperienceGlobeComponent.h
	Pickables/ExperienceGlobeComponent.cpp
)

set(UI_SOURCE
	UI/ExperienceBarComponent.h
	UI/ExperienceBarComponent.cpp
	UI/AmmoHUDComponent.h
	UI/AmmoHUDComponent.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${ACTOR_SOURCE}
	${PLAYER_SOURCE}
	${ENEMY_SOURCE}
	${STATES_SOURCE}
	${PICKABLES_SOURCE}
	${UI_SOURCE}
)