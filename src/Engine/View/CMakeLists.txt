set(SOURCES
	IViewStrategy.h
	Renderables.h
	ConsoleViewStrategy.h
	ConsoleViewStrategy.cpp
	WindowViewStrategy.h
	WindowViewStrategy.cpp
	IGuiView.h
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
