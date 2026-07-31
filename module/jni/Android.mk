LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := zygisk_module
LOCAL_CFLAGS := -std=c++17 -frtti -fexceptions
LOCAL_LDFLAGS := -llog -lEGL -lGLESv3 -landroid

LOCAL_SRC_FILES := \
    main.cpp \
    imgui/imgui.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_tables.cpp \
    imgui/imgui_widgets.cpp \
    imgui/imgui_backend_egl.cpp \
    hook/TouchHook.cpp \
    hook/HookEngine.cpp \
    hook/GraphicsHook.cpp

include $(BUILD_SHARED_LIBRARY)
