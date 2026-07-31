#include "TouchHook.h"
#include <jni.h>
#include <android/input.h>
#include <android/looper.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "TouchHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace TouchHook {
    bool g_menuVisible = false;

    void Init() {
        LOGD("Touch hook initialized");
    }

    bool IsMenuVisible() {
        return g_menuVisible;
    }

    void SetMenuVisible(bool visible) {
        g_menuVisible = visible;
    }
}
=== END FILE ===
