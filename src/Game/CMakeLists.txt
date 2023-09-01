set(GAME_PROJECT GameLib)
set(GAME_PROJECT GameLib PARENT_SCOPE)

project(
  ${GAME_PROJECT}
  VERSION 1.0
  LANGUAGES CXX
)

add_library(
  ${PROJECT_NAME} STATIC
  Game.cpp
	GameInjection.h
 )

add_subdirectory(Managers)
add_subdirectory(Components)
add_subdirectory(Skills)
add_subdirectory(Core)
add_subdirectory(Scenes)

target_include_directories(
  ${GAME_PROJECT}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${SFML_INCLUDE}
)

target_link_libraries(
	${GAME_PROJECT}
  PUBLIC
  ${ENGINE_PROJECT}
)