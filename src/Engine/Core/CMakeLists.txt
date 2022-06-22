set(SOURCES
	ApplicationInjection.h
	ColliderData.h
	EventData.h
	Events.h
	CameraData.h

	GameObject/GameObjectTag.h
	GameObject/GameObject.h
	GameObject/GameObject.inl
	GameObject/GameObject.cpp

	Scene/Scene.h
	Scene/Scene.cpp
	Scene/SceneLoader.h
	Scene/SceneLoader.cpp

	StateMachine/IState.h
	StateMachine/BasicSceneState.h
	StateMachine/BasicSceneState.cpp
	StateMachine/StateContainer.h
	StateMachine/StateContainer.inl
	StateMachine/StateContainer.cpp

	Serializing/SceneSerializer.h
	Serializing/SceneSerializer.cpp

	Messaging/MessageTypes.h
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
