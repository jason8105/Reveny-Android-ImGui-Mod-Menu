cmake_minimum_required(VERSION 3.18)

project(ZygiskImGuiTouch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -frtti")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_library(zygisk_module SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/HookEngine.cpp
    src/main/cpp/TouchHook.cpp
    src/main/cpp/ImGuiHook.cpp
)

target_include_directories(zygisk_module PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main/cpp
    ${CMAKE_SOURCE_DIR}/src/main/cpp/imgui
    ${CMAKE_SOURCE_DIR}/src/main/cpp/imgui/backends
)

find_library(log-lib log)

target_link_libraries(zygisk_module
    ${log-lib}
    android
    EGL
    GLESv3
)
