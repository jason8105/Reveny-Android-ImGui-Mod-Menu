cmake_minimum_required(VERSION 3.22)
project(RevenyImGui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DLOG_TAG="RevenyImGui")

include_directories(
    app/src/main/cpp
    app/src/main/cpp/imgui
    app/src/main/cpp/imgui/backends
    app/src/main/cpp/dobby/include
    app/src/main/cpp/dobby
)

file(GLOB_RECURSE SRC_FILES
    "app/src/main/cpp/*.cpp"
    "app/src/main/cpp/*.cc"
    "app/src/main/cpp/*.c"
    "app/src/main/cpp/imgui/*.cpp"
    "app/src/main/cpp/imgui/backends/*.cpp"
    "app/src/main/cpp/dobby/*.cpp"
    "app/src/main/cpp/dobby/*.c"
    "app/src/main/cpp/dobby/*.cc"
    "app/src/main/cpp/KittyMemory/src/*.cpp"
    "app/src/main/cpp/KittyMemory/include/*.h"
)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found. Check if KittyMemory submodule is initialized.")
endif()

add_library(RevenyImGui SHARED
    ${SRC_FILES}
)

target_link_libraries(
    RevenyImGui
    log
    android
    dl
)
