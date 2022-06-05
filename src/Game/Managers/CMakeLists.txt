set(MANAGERS_SOURCE
	GameManager.h
	GameManager.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${MANAGERS_SOURCE}
)