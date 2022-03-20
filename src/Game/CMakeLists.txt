project(
    Game
    VERSION 1.0
    LANGUAGES CXX
)

# COMPONENTS
set(SRC_GAME_COMPONENTS

)

add_executable(
    ${PROJECT_NAME}
    Game.cpp
	GameInjection.h
	${SRC_GAME_COMPONENTS}
)

 target_link_libraries(
	${PROJECT_NAME} 
	PUBLIC 
	Engine
)