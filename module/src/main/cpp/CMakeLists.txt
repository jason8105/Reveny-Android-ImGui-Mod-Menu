cmake_minimum_required(VERSION 3.22.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
    reveny
    SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/imgui/imgui.cpp
    src/main/cpp/imgui/imgui_draw.cpp
    src/main/cpp/imgui/imgui_tables.cpp
    src/main/cpp/imgui/imgui_widgets.cpp
    src/main/cpp/imgui/imgui_backend.cpp
    src/main/cpp/hooks/HookEngine.cpp
    src/main/cpp/hooks/TouchHook.cpp
)

target_include_directories(
    reveny
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp
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
    OpenGLESv3
)

target_link_libraries(
    reveny
    ${log-lib}
    ${android-lib}
    ${egl-lib}
    ${gpu-lib}
)
=== END FILE ===
