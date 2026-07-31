cmake_minimum_required(VERSION 3.27.0)

project(ModMenu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(android-lib log)

# Dobby Hook
include_directories(${CMAKE_SOURCE_DIR}/external/dobby)

# KittyMemory
include_directories(${CMAKE_SOURCE_DIR}/external/KittyMemory)

# ImGui
include_directories(${CMAKE_SOURCE_DIR}/external/imgui)
include_directories(${CMAKE_SOURCE_DIR}/external/imgui/backends)

add_library(${CMAKE_PROJECT_NAME} SHARED
    src/main/cpp/native-lib.cpp
    external/dobby/dobby.cpp
    external/KittyMemory/src/KittyMemory.cpp
    external/KittyMemory/src/KittyUtils.cpp
    external/KittyMemory/src/KittyLogger.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_android.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${android-lib}
    log
    android
    EGL
    GLESv3
    z
)
