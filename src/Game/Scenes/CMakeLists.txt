set(SCENES_SOURCE
	GamePlayScene.h
	GamePlayScene.cpp
	MainMenuScene.h
	MainMenuScene.cpp
	SplashScreenScene.h
	SplashScreenScene.cpp

	Shared/GameMenuScene.h
	Shared/GameMenuScene.cpp
	Shared/SettingsScreenScene.h
	Shared/SettingsScreenScene.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${SCENES_SOURCE}
)