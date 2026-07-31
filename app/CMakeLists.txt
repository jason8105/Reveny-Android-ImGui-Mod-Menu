cmake_minimum_required(VERSION 3.22.1)

project(ImGuiModule)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required libraries
find_library(log-lib log)
find_library(egl-lib EGL)
find_library(glesv2-lib GLESv2)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/hook)

# ImGui Sources
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

# Hook Sources
set(HOOK_SOURCES
    hook/TouchHook.cpp
    hook/HookEngine.cpp
    hook/GraphicsHook.cpp
)

# Add library
add_library(ImGuiModule SHARED
    main.cpp
    ${IMGUI_SOURCES}
    ${HOOK_SOURCES}
)

# Link libraries
target_link_libraries(ImGuiModule
    ${log-lib}
    ${egl-lib}
    ${glesv2-lib}
    android
)

# Set compile options
target_compile_options(ImGuiModule PRIVATE
    -frtti
    -fexceptions
    -Wno-invalid-offsetof
)
