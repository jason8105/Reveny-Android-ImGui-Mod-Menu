#include "TouchHook.h"
#include <android/input.h>
#include <jni.h>
#include <cstring>

namespace TouchHook {

static AInputQueue* g_inputQueue = nullptr;
static bool g_menuVisible = false;

int TouchHook::HookAInputQueue_getEvent(JNIEnv* env, jobject thiz, AInputQueue* queue) {
    g_inputQueue = queue;
    
    if (g_inputQueue) {
        AInputEvent* event = nullptr;
        int result = AInputQueue_getEvent(g_inputQueue, &event);
        
        if (result >= 0 && event) {
            if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
                if (g_menuVisible) {
                    // Process touch for ImGui menu
                    float x = AMotionEvent_getX(event, 0);
                    float y = AMotionEvent_getY(event, 0);
                    int action = AMotionEvent_getAction(event);
                    
                    // Pass to ImGui for menu interaction
                    // ImGui handles the touch here
                }
            }
        }
        
        return result;
    }
    
    return -1;
}

void TouchHook::SetMenuVisible(bool visible) {
    g_menuVisible = visible;
}

bool TouchHook::IsMenuVisible() {
    return g_menuVisible;
}

} // namespace TouchHook
=== END FILE ===
