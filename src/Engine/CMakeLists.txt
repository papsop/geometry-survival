set(ENGINE_PROJECT Engine)
set(ENGINE_PROJECT Engine PARENT_SCOPE)
find_package(OpenGL REQUIRED)

project(
    ${ENGINE_PROJECT}
    VERSION 1.0
    LANGUAGES CXX
)

add_library(
    ${ENGINE_PROJECT} STATIC
    Application.h
    Application.inl
    Application.cpp
)

add_subdirectory(Managers)
add_subdirectory(Debug)
add_subdirectory(Components)
add_subdirectory(Utils)
add_subdirectory(Core)
add_subdirectory(ImGui)

# PRIVATE because we don't want to propagate
target_include_directories(
    ${ENGINE_PROJECT}
    PRIVATE
    ${SFML_INCLUDE}
    ${YAML_INCLUDE}
)

# PUBLIC because we want to propagate SFML into Game as well without explicit linking there
target_link_libraries(
	${ENGINE_PROJECT}
	PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    box2d
    yaml-cpp
    ${OPENGL_LIBRARIES}
)