cmake_minimum_required(VERSION 3.22.1)

project(ZygiskImGui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(log-lib log)

add_library(
    zygisk_module
    SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/imgui/imgui.cpp
    src/main/cpp/imgui/imgui_draw.cpp
    src/main/cpp/imgui/imgui_tables.cpp
    src/main/cpp/imgui/imgui_widgets.cpp
    src/main/cpp/imgui/imgui_impl_opengl3.cpp
    src/main/cpp/imgui/imgui_impl_android.cpp
    src/main/cpp/hook/HookEngine.cpp
    src/main/cpp/hook/TouchHook.cpp
)

target_link_libraries(
    zygisk_module
    ${log-lib}
    android
    EGL
    GLESv3
)

target_compile_options(zygisk_module PRIVATE -fexceptions -frtti)
target_compile_definitions(zygisk_module PRIVATE IMGUI_IMPL_OPENGL_LOADER_EGL)

=== END FILE ===
