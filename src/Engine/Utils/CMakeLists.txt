set(SOURCES
	AllUtils.h
	IdGenerator.h
	VectorUtils.h
	VectorUtils.cpp
	Nuklear_SFML.hpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
