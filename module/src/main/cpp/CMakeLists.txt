cmake_minimum_required(VERSION 3.18.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANDROID_STL c++_shared)

add_library(${CMAKE_PROJECT_NAME} SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/imgui/imgui.cpp
    src/main/cpp/imgui/imgui_draw.cpp
    src/main/cpp/imgui/imgui_tables.cpp
    src/main/cpp/imgui/imgui_widgets.cpp
    src/main/cpp/imgui/imgui_backend.cpp
    src/main/cpp/hooks/HookEngine.cpp
    src/main/cpp/hooks/TouchHook.cpp
    src/main/cpp/hooks/GraphicsHook.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp
    ${CMAKE_SOURCE_DIR}/src/main/cpp/imgui
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    android
    log
    EGL
    GLESv3
)
=== END FILE ===
