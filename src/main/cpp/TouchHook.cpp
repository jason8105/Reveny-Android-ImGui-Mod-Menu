#include "TouchHook.h"
#include "HookEngine.h"
#include <android/input.h>
#include <android/looper.h>
#include <android/log.h>
#include <cstring>

#define LOG_TAG "TouchHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool TouchHook::menuOpen = false;
void* TouchHook::originalAInputQueue_getEvent = nullptr;
void* TouchHook::originalAInputQueue_getFd = nullptr;

void TouchHook::init() {
    LOGD("TouchHook initializing...");
    
    HookEngine::PltHookFunction("libandroid_runtime.so", "AInputQueue_getEvent", 
        reinterpret_cast<void*>(hookAInputQueue_getEvent), &originalAInputQueue_getEvent);
    
    HookEngine::PltHookFunction("libandroid_runtime.so", "AInputQueue_getFd",
        reinterpret_cast<void*>(hookAInputQueue_getFd), &originalAInputQueue_getFd);
    
    LOGD("TouchHook initialized");
}

void TouchHook::cleanup() {
    LOGD("TouchHook cleanup");
    menuOpen = false;
}

bool TouchHook::isMenuOpen() {
    return menuOpen;
}

void TouchHook::setMenuOpen(bool open) {
    menuOpen = open;
}

void* TouchHook::hookAInputQueue_getEvent(void* queue) {
    if (originalAInputQueue_getEvent) {
        return reinterpret_cast<void*>(originalAInputQueue_getEvent)(queue);
    }
    return nullptr;
}

void* TouchHook::hookAInputQueue_getFd(void* queue) {
    if (originalAInputQueue_getFd) {
        return reinterpret_cast<void*>(originalAInputQueue_getFd)(queue);
    }
    return nullptr;
}
