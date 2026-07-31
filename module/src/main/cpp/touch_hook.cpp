#include <jni.h>
#include <string>
#include <vector>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "RevenyTouch"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace TouchHook {

void Init() {
    LOGD("TouchHook initialized");
}

bool IsMenuOpen() {
    return false;
}

}

extern "C" {

void touch_hook_init() {
    TouchHook::Init();
    LOGD("Touch hook initialized");
}

}
=== END FILE ===
