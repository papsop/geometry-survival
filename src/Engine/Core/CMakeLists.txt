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
	Scene/IScene.h


	StateMachine/IState.h
	StateMachine/PushdownStateMachine.h
	StateMachine/PushdownStateMachine.inl

	Serializing/SceneSerializer.h
	Serializing/SceneSerializer.cpp

	Messaging/MessageTypes.h

	Signal.h
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
