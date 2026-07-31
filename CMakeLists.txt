cmake_minimum_required(VERSION 3.18)

project(ImGuiTouchHook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/HookEngine.cpp
    src/TouchHook.cpp
    src/ImGuiHook.cpp
    src/Utils.cpp
)

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ANDROID_NDK}/sources/android/cpufeatures
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    android
    log
    EGL
    GLESv3
    jnigraphics
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

=== END FILE ===
