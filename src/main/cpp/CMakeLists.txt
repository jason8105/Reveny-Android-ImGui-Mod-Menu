cmake_minimum_required(VERSION 3.22.1)

project("RevenyModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(log-lib log)

add_library(
        reveny-mod-menu
        SHARED
        src/main/cpp/main.cpp
        src/main/cpp/hook_engine.cpp
        src/main/cpp/imgui_renderer.cpp
        src/main/cpp/touch_hook.cpp
)

target_link_libraries(
        reveny-mod-menu
        ${log-lib}
        android
        EGL
        GLESv3
        jnigraphics
)

=== END FILE ===
