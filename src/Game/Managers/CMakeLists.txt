set(MANAGERS_SOURCE
	GameManager.h
	GameManager.cpp
	SkillsManager.h
	SkillsManager.cpp
	EnemySpawningManager.h
	EnemySpawningManager.cpp

	GameTimer.h
	GameTimer.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${MANAGERS_SOURCE}
)