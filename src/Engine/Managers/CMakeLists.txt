set(SOURCES
	AllManagers.h
	DatabaseManager.h
	DatabaseManager.cpp
	EventManager.h
	EventManager.cpp
	GameObjectManager.h
	GameObjectManager.cpp
	InputManager.h
	InputManager.cpp
	SceneManager.h
	SceneManager.cpp
	SubsystemManager.h
	SubsystemManager.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
