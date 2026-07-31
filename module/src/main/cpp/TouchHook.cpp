#include "TouchHook.h"
#include <jni.h>
#include <android/input.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "TouchHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static bool g_menu_visible = false;
static bool g_initialized = false;

void TouchHook::Initialize() {
    if (g_initialized) return;
    
    LOGD("TouchHook initialized");
    g_initialized = true;
}

void TouchHook::SetMenuVisible(bool visible) {
    g_menu_visible = visible;
    LOGD("Menu visibility set to: %d", visible);
}

void TouchHook::Cleanup() {
    g_menu_visible = false;
    g_initialized = false;
    LOGD("TouchHook cleanup completed");
}

bool TouchHook::IsMenuVisible() {
    return g_menu_visible;
}
=== END FILE ===
