cmake_minimum_required(VERSION 3.18.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANDROID_STL c++_shared)

add_library(${CMAKE_PROJECT_NAME} SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGui/imgui.cpp
    src/main/cpp/ImGui/imgui_demo.cpp
    src/main/cpp/ImGui/imgui_draw.cpp
    src/main/cpp/ImGui/imgui_tables.cpp
    src/main/cpp/ImGui/imgui_widgets.cpp
    src/main/cpp/ImGui/imgui_backend.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp
    ${CMAKE_SOURCE_DIR}/src/main/cpp/ImGui
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    android
    log
    EGL
    GLESv3
    jnigraphics
)
=== END FILE ===
