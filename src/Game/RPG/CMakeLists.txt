set(RPG_SOURCE
	RPGStats.h
	RPGActor.h
	RPGActor.cpp

	Buff/Buff.h
	Buff/Buff.cpp
)

target_sources(${GAME_PROJECT} PUBLIC 
	${RPG_SOURCE}
)