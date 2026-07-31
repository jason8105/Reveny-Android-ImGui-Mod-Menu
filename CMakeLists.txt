cmake_minimum_required(VERSION 3.18.1)

project(RevenyModMenu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(modmenu SHARED
    src/main/cpp/native-lib.cpp
)

set(LINKER_FLAGS "-Wl,--wrap=dlopen -Wl,--wrap=eglSwapBuffers")

target_link_libraries(modmenu
    log
    android
    EGL
    GLESv3
    m
    z
)

set_target_properties(modmenu PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

if(ANDROID_ABI STREQUAL "arm64-v8a")
    set_target_properties(modmenu PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/arm64-v8a
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/arm64-v8a
    )
endif()
