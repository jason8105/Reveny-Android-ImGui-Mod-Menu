cmake_minimum_required(VERSION 3.22.1)

project("RevenyModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
    reveny_mod_menu
    SHARED
    src/main/cpp/main.cpp
    src/main/cpp/hook_engine.cpp
    src/main/cpp/imgui_renderer.cpp
    src/main/cpp/touch_hook.cpp
)

target_include_directories(
    reveny_mod_menu
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp/include
    ${CMAKE_SOURCE_DIR}/src/main/cpp/imgui
)

find_library(
    log-lib
    log
)

find_library(
    android-lib
    android
)

find_library(
    egl-lib
    EGL
)

find_library(
    gpu-lib
    GLESv3
)

find_library(
    input-lib
    input
)

target_link_libraries(
    reveny_mod_menu
    ${log-lib}
    ${android-lib}
    ${egl-lib}
    ${gpu-lib}
    ${input-lib}
    android
)
=== END FILE ===
