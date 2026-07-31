LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := zygisk-imgui-touch-fix
LOCAL_CFLAGS := -std=c++17 -fexceptions -frtti
LOCAL_CPPFLAGS := -std=c++17 -fexceptions -frtti
LOCAL_LDFLAGS := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lOpenSLES
LOCAL_SRC_FILES := \
    src/HookEngine.cpp \
    src/TouchHook.cpp \
    src/ImGuiHook.cpp \
    src/TouchInjection.cpp \
    src/ImGuiRenderer.cpp \
    src/main.cpp

include $(BUILD_SHARED_LIBRARY)
=== END FILE ===
