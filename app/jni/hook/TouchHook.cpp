#include "TouchHook.h"
#include <android/input.h>
#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <sys/system_properties.h>

static int (*original_AInputQueue_getEvent)(AInputQueue* queue, AInputEvent* event) = nullptr;
static bool s_touchHookActive = true;

static int hook_AInputQueue_getEvent(AInputQueue* queue, AInputEvent* event) {
    if (!s_touchHookActive) {
        return original_AInputQueue_getEvent(queue, event);
    }
    
    int result = original_AInputQueue_getEvent(queue, event);
    
    if (result == 0 && event) {
        if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
            // Process touch event for ImGui
            float x = AMotionEvent_getX(event, 0);
            float y = AMotionEvent_getY(event, 0);
            // Handle touch for ImGui here
        }
    }
    
    return result;
}

void TouchHook::Initialize() {
    void* lib = dlopen("libcutils.so", RTLD_NOW);
    if (!lib) {
        return;
    }
    
    original_AInputQueue_getEvent = (decltype(original_AInputQueue_getEvent))dlsym(lib, "AInputQueue_getEvent");
    if (original_AInputQueue_getEvent) {
        PltHook::HookFunction(original_AInputQueue_getEvent, hook_AInputQueue_getEvent, 
                              reinterpret_cast<void**>(&original_AInputQueue_getEvent));
    }
}

bool TouchHook::IsHookActive() {
    return s_touchHookActive;
}

void TouchHook::SetHookActive(bool active) {
    s_touchHookActive = active;
}
