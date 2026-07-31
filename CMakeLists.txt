cmake_minimum_required(VERSION 3.22)

project(RevenyModMenu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# KittyMemory
set(KITTYMEMORY_DIR ${CMAKE_SOURCE_DIR}/app/src/main/cpp/KittyMemory)
add_subdirectory(${KITTYMEMORY_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/app/src/main/cpp/imgui)
add_subdirectory(${IMGUI_DIR})

# HookEngine/Dobby
set(HOOK_ENGINE_DIR ${CMAKE_SOURCE_DIR}/app/src/main/cpp/HookEngine)
add_subdirectory(${HOOK_ENGINE_DIR})

# Main module source
set(MODULE_SOURCES
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/native-lib.cpp
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/HookEngine/HookEngine.cpp
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/HookEngine/PltHook.cpp
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/HookEngine/Logger.cpp
    ${KITTYMEMORY_DIR}/KittyMemory.cpp
    ${KITTYMEMORY_DIR}/KittyOS.cpp
    ${KITTYMEMORY_DIR}/KittyUtils.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_backends/imgui_impl_android.cpp
    ${IMGUI_DIR}/imgui_backends/imgui_impl_opengles2.cpp
)

# Touch hooks
set(TOUCH_HOOKS
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/touch/AInputQueue.cpp
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/touch/TouchHook.cpp
)

add_library(${CMAKE_PROJECT_NAME} SHARED
    ${MODULE_SOURCES}
    ${TOUCH_HOOKS}
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/KittyMemory
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/HookEngine
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/imgui
    ${CMAKE_SOURCE_DIR}/app/src/main/cpp/imgui/backends
)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    log
    jnigraphics
    EGL
    GLESv2
    pthread
    m
)

# Android specific settings
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -fpermissive
    -frtti
    -fexceptions
    -Wno-error=format-security
)
