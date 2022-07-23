set(SOURCES
	AllUtils.h
	IdGenerator.h
	VectorUtils.h
	VectorUtils.cpp
	CvarUtils.h
	CvarUtils.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
