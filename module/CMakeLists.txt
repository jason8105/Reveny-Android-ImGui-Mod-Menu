cmake_minimum_required(VERSION 3.22.1)

project(ZygiskImGuiModule)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required libraries
find_library(log-lib log)

# Zygisk Headers
set(ZYGISK_HEADER_DIR ${ANDROID_NDK}/../../sysroot/usr/include)

# Include directories
include_directories(${ZYGISK_HEADER_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# ImGui Sources
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_backend_egl.cpp
)

# Hook Sources
set(HOOK_SOURCES
    hook/TouchHook.cpp
    hook/HookEngine.cpp
    hook/GraphicsHook.cpp
)

# Add library
add_library(zygisk_module SHARED
    main.cpp
    ${IMGUI_SOURCES}
    ${HOOK_SOURCES}
)

# Link libraries
target_link_libraries(zygisk_module
    ${log-lib}
    EGL
    GLESv3
    android
)

# Set compile options
target_compile_options(zygisk_module PRIVATE
    -frtti
    -fexceptions
    -Wno-invalid-offsetof
)
