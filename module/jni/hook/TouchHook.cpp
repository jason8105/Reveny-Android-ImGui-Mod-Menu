#include "TouchHook.h"
#include <jni.h>
#include <dlfcn.h>
#include <cstring>

static bool s_touchHookActive = true;

void TouchHook::Initialize() {
    // Initialize touch hook for Zygisk
    s_touchHookActive = true;
}

bool TouchHook::IsHookActive() {
    return s_touchHookActive;
}

void TouchHook::SetHookActive(bool active) {
    s_touchHookActive = active;
}
