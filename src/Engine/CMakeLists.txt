set(ENGINE_PROJECT Engine)
set(ENGINE_PROJECT Engine PARENT_SCOPE)

project(
    ${ENGINE_PROJECT}
    VERSION 1.0
    LANGUAGES CXX
)

add_library(
    ${ENGINE_PROJECT} STATIC
    Application.cpp
    Application.h
 "Components/Physics/PhysicsBodyComponent.h" "Components/Physics/PhysicsBodyComponent.cpp" "Components/Physics/CircleFixtureComponent.cpp" "Components/View/CameraComponent.h")

add_subdirectory(Subsystems)
add_subdirectory(Managers)
add_subdirectory(Debug)
add_subdirectory(Components)
add_subdirectory(Utils)
add_subdirectory(View)
add_subdirectory(Core)

# PRIVATE because we don't want to propagate
target_include_directories(
    ${ENGINE_PROJECT}
    PRIVATE
    ${SFML_INCLUDE}
)

# PUBLIC because we want to propagate SFML into Game as well without explicit linking there
target_link_libraries(
	${ENGINE_PROJECT}
	PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    box2d
)