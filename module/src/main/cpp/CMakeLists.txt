cmake_minimum_required(VERSION 3.18)
project(RevenyModMenu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_library(log-lib log)

add_library(RevenyModMenu SHARED
    AndroidJNI.cpp
    HookEngine.cpp
    TouchHook.cpp
    ImGuiRenderer.cpp
    GraphicsHook.cpp
)

target_link_libraries(RevenyModMenu
    ${log-lib}
    android
    EGL
    GLESv3
)

target_compile_options(RevenyModMenu PRIVATE
    -fexceptions
    -frtti
    -O2
)
=== END FILE ===
