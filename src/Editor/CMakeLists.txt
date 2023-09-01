set(EDITOR_PROJECT Editor)
set(EDITOR_PROJECT Editor PARENT_SCOPE)

project(
  ${EDITOR_PROJECT}
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(
  ${PROJECT_NAME}
  Main.cpp
 )

target_include_directories(
  ${EDITOR_PROJECT}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${SFML_INCLUDE}
)

target_link_libraries(
	${EDITOR_PROJECT}
  PUBLIC
  ${GAME_PROJECT}
)