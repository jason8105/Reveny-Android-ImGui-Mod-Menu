cmake_minimum_required(VERSION 3.22.1)

project("RevenyModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${CMAKE_PROJECT_NAME} SHARED
    src/main/cpp/main.cpp
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGuiHook.cpp
)

find_library(log-lib log)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${log-lib}
    android
    EGL
    GLESv3
)
=== END FILE ===
