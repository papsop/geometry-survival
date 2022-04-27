set(SOURCES
	AllUtils.h
	json.hpp
	pugiconfig.hpp
	pugixml.cpp
	pugixml.hpp
	IdGenerator.h
	VectorUtils.h
	VectorUtils.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
