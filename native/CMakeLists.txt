cmake_minimum_required(VERSION 3.22)

project(RevenyNative)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(RevenyNative SHARED
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGuiRenderer.cpp
    src/main/cpp/main.cpp
)

find_library(log-lib log)

target_link_libraries(RevenyNative
    ${log-lib}
    android
    EGL
    GLESv3
)
=== END FILE ===
