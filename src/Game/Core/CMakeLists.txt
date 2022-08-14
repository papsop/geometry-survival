set(CORE_SOURCE
	EventData.h	

	GameObject/GameObjectFactory.h
	GameObject/GameObjectFactory.cpp
	GameObject/FactoryDefinitions.h

	RPG/Buff.h
	RPG/Buff.cpp
	RPG/RPGStats.h
)

target_sources(${GAME_PROJECT} PUBLIC 
	${CORE_SOURCE}
)