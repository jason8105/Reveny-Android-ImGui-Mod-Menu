cmake_minimum_required(VERSION 3.22.1)

project("ImGuiModMenu")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(NDK_SUPPORT_HEADERS_DIR
    ${PROJECT_SOURCE_DIR}/KittyMemory/MemoryProcessHelper/include
    ${PROJECT_SOURCE_DIR}/KittyMemory/SymHook/include
    ${PROJECT_SOURCE_DIR}/KittyMemory/Utils/include)

set(NDK_LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

set(NDK_INCLUDE_DIRS
    ${NDK_SUPPORT_HEADERS_DIR})

add_definitions(-DLOG_TAG=\"ImGuiModMenu\")

set(NDK_LIBS
    # Add your static libraries here
)

# Add native source
add_library(imgui_native SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/Hooks/TouchHook.cpp
    src/main/cpp/Hooks/ImGuiHook.cpp
    src/main/cpp/Hooks/HookEngine.cpp
    src/main/cpp/utils/Utils.cpp
    src/main/cpp/Imgui/ImGui.cpp
)

target_link_libraries(
    imgui_native
    android
    log
    EGL
    GLESv2
    m
    z
    ${NDK_LIBS})

set_target_properties(imgui_native PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/src/main/cpp)
include_directories(${PROJECT_SOURCE_DIR}/KittyMemory)
