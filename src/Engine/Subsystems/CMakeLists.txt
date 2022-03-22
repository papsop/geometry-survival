set(SOURCES
	ComponentSubsystem.h
	ComponentSubsystem.cpp
	PhysicsSubsystem.h
	PhysicsSubsystem.cpp
	ViewSubsystem.h
	ViewSubsystem.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
