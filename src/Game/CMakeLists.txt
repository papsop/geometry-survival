set(GAME_PROJECT Game)
set(GAME_PROJECT Game PARENT_SCOPE)

project(
    ${GAME_PROJECT}
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(
    ${PROJECT_NAME}
    Game.cpp
	GameInjection.h
)

add_subdirectory(Managers)
add_subdirectory(Components)
add_subdirectory(Core)

target_include_directories(
    ${GAME_PROJECT}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${SFML_INCLUDE}
)

target_link_libraries(
	${GAME_PROJECT}
    PRIVATE
    ${ENGINE_PROJECT}
)