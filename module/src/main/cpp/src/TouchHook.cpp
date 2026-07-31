#include "TouchHook.h"
#include <android/input.h>
#include <android/looper.h>
#include <jni.h>
#include <cstring>

namespace TouchHook {

static bool touchHookEnabled = false;
static bool menuVisible = false;

void EnableTouchHook(bool enable) {
    touchHookHookEnabled = enable;
}

bool IsTouchHookEnabled() {
    return touchHookEnabled;
}

void SetMenuVisible(bool visible) {
    menuVisible = visible;
}

bool IsMenuVisible() {
    return menuVisible;
}

int32_t HookAInputQueue_getEvent(AInputQueue* queue, AInputEvent* event) {
    if (touchHookEnabled && menuVisible && event) {
        AInputEvent_type type = AInputEvent_getType(event);
        if (type == AINPUT_EVENT_TYPE_MOTION) {
            int32_t action = AMotionEvent_getAction(event);
            int32_t actionCode = action & AMOTION_EVENT_ACTION_MASK;
            
            if (actionCode == AMOTION_EVENT_ACTION_DOWN || 
                actionCode == AMOTION_EVENT_ACTION_UP ||
                actionCode == AMOTION_EVENT_ACTION_MOVE) {
                float x = AMotionEvent_getX(event, 0);
                float y = AMotionEvent_getY(event, 0);
                
                ImGuiIO& io = ImGui::GetIO();
                io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
                io.AddMousePosEvent(x, y);
                io.AddMouseButtonEvent(0, actionCode == AMOTION_EVENT_ACTION_DOWN);
            }
        }
    }
    
    return 0;
}

}
=== END FILE ===
