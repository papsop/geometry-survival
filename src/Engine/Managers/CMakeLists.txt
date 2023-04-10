set(SOURCES
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
	ViewLayers.h
	ComponentManager.h
	ComponentManager.inl
	ComponentManager.cpp
	ConfigManager.h
	ConfigManager.cpp
	UIManager.h
	UIManager.cpp
	ResourceManager.h
	ResourceManager.cpp

	Config/IConfigurable.h
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
