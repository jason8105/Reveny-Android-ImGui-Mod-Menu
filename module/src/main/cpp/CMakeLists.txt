cmake_minimum_required(VERSION 3.22.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(log REQUIRED)

add_library(
    reveny
    SHARED
    src/main/cpp/main.cpp
    src/main/cpp/hook.cpp
    src/main/cpp/imgui.cpp
    src/main/cpp/touch_hook.cpp
)

target_link_libraries(
    reveny
    log
    android
    EGL
    GLESv3
)
=== END FILE ===
