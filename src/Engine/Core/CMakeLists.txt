set(SOURCES
	ApplicationInjection.h
	ColliderData.h
	EventData.h
	Events.h
	GameObject.h
	GameObject.cpp
	Scene.h
	Scene.cpp
	CameraData.h
	Config.h

	StateMachine/IState.h
	StateMachine/BasicSceneState.h
	StateMachine/BasicSceneState.cpp

	Serializing/SceneSerializer.h
	Serializing/SceneSerializer.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
