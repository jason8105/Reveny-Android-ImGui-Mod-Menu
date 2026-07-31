cmake_minimum_required(VERSION 3.22.1)

project(RevenyImGui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Zygisk headers
set(ZYGISK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../../../../../include)

# ImGui sources
set(IMGUI_SOURCES
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_backend.cpp
)

# Hook sources
set(HOOK_SOURCES
    src/HookEngine.cpp
    src/TouchHook.cpp
    src/GraphicsHook.cpp
    src/ImGuiRenderer.cpp
)

# Main library
add_library(RevenyImGui SHARED
    ${IMGUI_SOURCES}
    ${HOOK_SOURCES}
    src/main.cpp
)

target_include_directories(RevenyImGui PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${ZYGISK_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/imgui
)

target_link_libraries(RevenyImGui
    log
    android
    EGL
    GLESv3
)

target_compile_options(RevenyImGui PRIVATE
    -fvisibility=hidden
    -fvisibility-inlines-hidden
    -Wno-unused-parameter
    -Wno-unused-function
)

=== END FILE ===
