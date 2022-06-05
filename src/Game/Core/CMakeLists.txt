set(CORE_SOURCE
	
	GameObject/GameObjectFactory.h
	GameObject/GameObjectFactory.cpp
	GameObject/FactoryDefinitions.h
)

target_sources(${GAME_PROJECT} PUBLIC 
	${CORE_SOURCE}
)