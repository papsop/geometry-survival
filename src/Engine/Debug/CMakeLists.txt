set(SOURCES
	IDebuggable.h
	IDebuggable.cpp
	Logger.h
	Logger.cpp
	LoggerLevel.h
	
	Backend/IBackendStrategy.h
	Backend/ConsoleBackendStrategy.h
	Backend/ConsoleBackendStrategy.cpp
	Backend/WindowBackendStrategy.h
	Backend/WindowBackendStrategy.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
