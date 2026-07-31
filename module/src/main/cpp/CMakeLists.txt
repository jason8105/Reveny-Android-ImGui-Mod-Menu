cmake_minimum_required(VERSION 3.18.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_library(log-lib log)

add_library(RevenyImGui SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGuiHook.cpp
)

target_link_libraries(RevenyImGui
    ${log-lib}
    android
    EGL
    GLESv3
)
=== END FILE ===
