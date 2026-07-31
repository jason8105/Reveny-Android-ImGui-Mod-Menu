cmake_minimum_required(VERSION 3.18)

project(RevenyMod)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(RevenyMod SHARED
    src/main.cpp
    src/HookEngine.cpp
    src/TouchHook.cpp
    src/ImGuiHook.cpp
    src/Menu.cpp
)

target_include_directories(RevenyMod PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(RevenyMod
    log
    android
    EGL
    GLESv2
)

set_target_properties(RevenyMod PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
=== END FILE ===
