set(SOURCES
	AllManagers.h
	AssetsManager.h
	AssetsManager.cpp
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
