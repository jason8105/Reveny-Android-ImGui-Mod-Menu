cmake_minimum_required(VERSION 3.18.1)
project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# KittyMemory dependencies
set(KITTY_MEMORY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp/KittyMemory)
set(KITTY_MEMORY_INCLUDE_DIR ${KITTY_MEMORY_DIR}/include)
set(KITTY_MEMORY_SRC ${KITTY_MEMORY_DIR}/src/KittyMemory.cpp)

# Dobby dependencies
set(DOBBY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp/Dobby)

# ImGui dependencies
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp/ImGui)
set(IMGUI_SRC ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_backend_opengl.cpp ${IMGUI_DIR}/imgui_impl_android.cpp)

# Hook source
set(HOOK_SRC ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp/Hook.cpp)

# Main library
add_library(RevenyImGui SHARED
    ${KITTY_MEMORY_SRC}
    ${HOOK_SRC}
    ${IMGUI_SRC}
)

# Include directories
target_include_directories(RevenyImGui PRIVATE
    ${KITTY_MEMORY_INCLUDE_DIR}
    ${KITTY_MEMORY_DIR}/include/
    ${Dobby_DIR}/include
    ${IMGUI_DIR}/
)

# Android NDK libs
target_link_libraries(RevenyImGui
    android
    log
    EGL
    GLESv2
    m
    z
)

# Compiler flags
target_compile_options(RevenyImGui PRIVATE -Wall -fvisibility=hidden -fPIC)

# C++17 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
