project(
    Engine
    VERSION 1.0
    LANGUAGES CXX
)

# COMPONENTS
SET(SRC_ENGINE_COMPONENTS
    Core/ApplicationInjection.h
)

add_library(
    ${PROJECT_NAME}
    Application.cpp
    Application.h
    ${SRC_ENGINE_COMPONENTS}
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/..
)