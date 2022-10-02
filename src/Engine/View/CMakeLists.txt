set(SOURCES
	IViewStrategy.h
	Renderables.h
	ConsoleViewStrategy.h
	ConsoleViewStrategy.cpp
	WindowViewStrategy.h
	WindowViewStrategy.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
