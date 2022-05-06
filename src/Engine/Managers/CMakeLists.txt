set(SOURCES
	AllManagers.h
	IManager.h

	EventManager.h
	EventManager.inl
	EventManager.cpp
	GameObjectManager.h
	GameObjectManager.cpp
	InputManager.h
	InputManager.cpp
	SceneManager.h
	SceneManager.cpp
	PhysicsManager.h
	PhysicsManager.cpp
	ViewManager.h
	ViewManager.cpp
	ComponentManager.h
	ComponentManager.inl
	ComponentManager.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
