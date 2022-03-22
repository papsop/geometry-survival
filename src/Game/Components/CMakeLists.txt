set(ACTOR_SOURCE
	Actor/ActorComponent.h
	Actor/ActorComponent.cpp
	Actor/BulletComponent.h
	Actor/BulletComponent.cpp
	Actor/Commands.h
	Actor/Commands.cpp

	Actor/WeaponComponent.h
	Actor/WeaponComponent.cpp

	Actor/Weapons/IWeapon.h
	Actor/Weapons/PistolWeapon.h
	Actor/Weapons/PistolWeapon.cpp
)

set(PLAYER_SOURCE
	Player/Inputcomponent.h
	Player/Inputcomponent.cpp
	Player/TestComponent.h
	Player/TestComponent.cpp
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

target_sources(${GAME_PROJECT} PUBLIC 
	${ACTOR_SOURCE}
	${PLAYER_SOURCE}
	${SPLASH_SOURCE}
)