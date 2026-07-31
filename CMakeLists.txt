cmake_minimum_required(VERSION 3.22.1)

project(ZygiskImGuiTouch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
    zygisk_imgui_touch
    SHARED
    src/main/cpp/native-lib.cpp
    src/main/cpp/hook_engine.cpp
    src/main/cpp/imgui_hook.cpp
    src/main/cpp/touch_hook.cpp
    src/main/cpp/zygisk_hook.cpp
)

find_library(
    log-lib
    log
)

find_library(
    android-lib
    android
)

find_library(
    egl-lib
    EGL
)

find_library(
    gpu-lib
    GLESv2
)

find_library(
    input-lib
    input
)

target_link_libraries(
    zygisk_imgui_touch
    ${log-lib}
    ${android-lib}
    ${egl-lib}
    ${gpu-lib}
    ${input-lib}
    jnigraphics
)
