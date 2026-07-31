#include "TouchHook.h"
#include <jni.h>
#include <android/input.h>
#include <android/looper.h>
#include <dlfcn.h>
#include <cstring>
#include <android/log.h>

#define LOG_TAG "RevenyTouch"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

bool TouchHook::menuOpen = false;
void* TouchHook::originalAInputQueue_getEvent = nullptr;

void TouchHook::init() {
    LOGD("TouchHook initialized");
    
    void* inputHandle = dlopen("libandroid.so", RTLD_NOW);
    if (!inputHandle) {
        LOGD("Failed to load libandroid.so");
        return;
    }
    
    originalAInputQueue_getEvent = dlsym(inputHandle, "_Z18AInputQueue_getEventP10AInputQueueP10AInputEvent");
    if (!originalAInputQueue_getEvent) {
        LOGD("Failed to find AInputQueue_getEvent");
    } else {
        LOGD("Original AInputQueue_getEvent found at: %p", originalAInputQueue_getEvent);
    }
}

void TouchHook::injectTouch(int x, int y, int action) {
    menuOpen = true;
    LOGD("Touch injected: x=%d, y=%d, action=%d", x, y, action);
}

bool TouchHook::isMenuOpen() {
    return menuOpen;
}
=== END FILE ===
