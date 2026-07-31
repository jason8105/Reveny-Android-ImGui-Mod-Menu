LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := reveny_hook
LOCAL_SRC_FILES := main.cpp
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := imgui_dobby kitty_memory
LOCAL_CFLAGS := -std=c++17 -fexceptions -frtti
LOCAL_CPPFLAGS := -std=c++17 -fexceptions

include $(BUILD_SHARED_LIBRARY)
