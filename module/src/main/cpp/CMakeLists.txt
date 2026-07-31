cmake_minimum_required(VERSION 3.22.1)

project("RevenyModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_library(log-lib log)

add_library(
        reveny-mod-menu
        SHARED
        src/main/cpp/native-lib.cpp
        src/main/cpp/imgui/imgui.cpp
        src/main/cpp/imgui/imgui_draw.cpp
        src/main/cpp/imgui/imgui_tables.cpp
        src/main/cpp/imgui/imgui_widgets.cpp
        src/main/cpp/imgui/imgui_demo.cpp
        src/main/cpp/imgui/imgui_backend.cpp
        src/main/cpp/hooks/HookEngine.cpp
        src/main/cpp/hooks/TouchHook.cpp
        src/main/cpp/hooks/GraphicsHook.cpp
)

target_link_libraries(
        reveny-mod-menu
        ${log-lib}
        android
        EGL
        GLESv3
)
=== END FILE ===
