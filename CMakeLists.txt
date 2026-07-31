cmake_minimum_required(VERSION 3.22)
project(imgui_mod)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/kittymemory
)

# ImGui sources
file(GLOB IMGUI_SOURCES
    imgui/*.cpp
    imgui/backends/imgui_impl_android.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC imgui)

# Dobby sources
add_library(dobby STATIC
    dobby/dobby.cpp
)

add_library(kitty_memory STATIC
    kittymemory/memory.h
    kittymemory/detection.h
)

# Main hook library
add_library(reveny_hook SHARED
    src/main/jni/main.cpp
)

target_link_libraries(reveny_hook
    imgui
    dobby
    kitty_memory
    android
    log
    EGL
    GLESv2
)
