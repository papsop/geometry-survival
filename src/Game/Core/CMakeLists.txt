set(CORE_SOURCE
	EventData.h	

	GameObject/GameObjectFactory.h
	GameObject/GameObjectFactory.cpp
	GameObject/FactoryDefinitions.h

	RPG/Buff.h
	RPG/Buff.cpp
	RPG/RPGStats.h

	StateMachines/UIStateMachine.h
	StateMachines/UIStateMachine.cpp

	StateMachines/States/UI/UIState.h
	StateMachines/States/UI/GameHUDState.h
	StateMachines/States/UI/GameHUDState.cpp
	StateMachines/States/UI/GameMenuState.h
	StateMachines/States/UI/GameMenuState.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${CORE_SOURCE}
)