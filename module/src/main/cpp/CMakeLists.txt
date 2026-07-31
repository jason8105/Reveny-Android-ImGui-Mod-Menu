cmake_minimum_required(VERSION 3.22.1)

project("RevenyModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(RevenyModMenu SHARED
    src/main/cpp/main.cpp
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGuiHook.cpp
)

target_include_directories(RevenyModMenu PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp
    ${CMAKE_SOURCE_DIR}/../..
)

find_library(log-lib log)

target_link_libraries(RevenyModMenu
    ${log-lib}
    android
    EGL
    GLESv3
)
=== END FILE ===
