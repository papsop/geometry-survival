set(SOURCES
	AllUtils.h
	IdGenerator.h
	pugiconfig.hpp
	pugixml.hpp
	pugixml.cpp
	VectorUtils.h
	VectorUtils.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
