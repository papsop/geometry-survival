set(CORE_SOURCE
	EventData.h	

	GameObject/GameObjectFactory.h
	GameObject/GameObjectFactory.cpp
	GameObject/FactoryDefinitions.h

	RPG/Buff.h
	RPG/Buff.cpp
	RPG/FrozenBuff.h
	RPG/FrozenBuff.cpp
	RPG/BurningBuff.h
	RPG/BurningBuff.cpp
	RPG/RPGStats.h
)

target_sources(${GAME_PROJECT} PUBLIC 
	${CORE_SOURCE}
)