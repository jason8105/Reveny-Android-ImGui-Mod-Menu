cmake_minimum_required(VERSION 3.22.1)

project("RevenyImGui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(log-lib log)

add_library(
        reveny-modmenu
        SHARED
        src/main/cpp/main.cpp
        src/main/cpp/hook.cpp
        src/main/cpp/imgui.cpp
        src/main/cpp/touch_hook.cpp
        src/main/cpp/zygisk.cpp
)

target_include_directories(reveny-modmenu PRIVATE
        ${CMAKE_SOURCE_DIR}/src/main/cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/imgui
)

target_link_libraries(reveny-modmenu
        ${log-lib}
        android
        EGL
        GLESv3
)
=== END FILE ===
