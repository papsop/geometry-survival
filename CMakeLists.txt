cmake_minimum_required (VERSION 3.22.0)

project(Dungeons&Geometry VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

project(Dungeons&Geometry)

add_subdirectory(libs)
add_subdirectory(src)

# copy assets/dlls
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
# we want to build box2d.dll inside bin dir
set_target_properties(box2d
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(NOT TARGET box2d OR NOT TARGET sfml-system)
    message(FATAL_ERROR "Forgot to git submodule update?")
endif()

# cleanup for visual studio
set_target_properties(imgui PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(glad PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(glfw PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(sajson PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(testbed PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(unit_test PROPERTIES FOLDER "Libraries/Box2D")
set_target_properties(box2d PROPERTIES FOLDER "Libraries/Box2D")

set_target_properties(sfml-audio PROPERTIES FOLDER "Libraries/SFML")
set_target_properties(sfml-graphics PROPERTIES FOLDER "Libraries/SFML")
set_target_properties(sfml-main PROPERTIES FOLDER "Libraries/SFML")
set_target_properties(sfml-network PROPERTIES FOLDER "Libraries/SFML")
set_target_properties(sfml-system PROPERTIES FOLDER "Libraries/SFML")
set_target_properties(sfml-window PROPERTIES FOLDER "Libraries/SFML")