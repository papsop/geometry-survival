set(SOURCES
	IDebuggable.h
	IDebuggable.cpp
	Logger.h
	Logger.cpp
	LoggerLevel.h
	VisualDebugContext.h
	VisualDebugContext.cpp
	
	Backend/IBackendStrategy.h
	Backend/ConsoleBackendStrategy.h
	Backend/ConsoleBackendStrategy.cpp
	Backend/WindowBackendStrategy.h
	Backend/WindowBackendStrategy.cpp
	Backend/ImGuiBackendStrategy.h
	Backend/ImGuiBackendStrategy.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
