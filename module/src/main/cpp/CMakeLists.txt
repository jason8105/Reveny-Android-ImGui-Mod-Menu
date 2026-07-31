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

target_link_libraries(RevenyModMenu
    log
    android
    EGL
    GLESv3
    jnigraphics
)

find_library(egl-lib EGL)
find_library(glesv2-lib GLESv2)

target_link_libraries(RevenyModMenu
    ${egl-lib}
    ${glesv2-lib}
)
=== END FILE ===
