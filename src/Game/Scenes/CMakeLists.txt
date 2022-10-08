set(SCENES_SOURCE
	GamePlayScene.h
	GamePlayScene.cpp
	MainMenuScene.h
	MainMenuScene.cpp
	SplashScreenScene.h
	SplashScreenScene.cpp

	Shared/GameMenuScene.h
	Shared/GameMenuScene.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${SCENES_SOURCE}
)