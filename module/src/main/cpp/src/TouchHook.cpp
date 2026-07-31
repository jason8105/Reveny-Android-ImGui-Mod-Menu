#include "TouchHook.h"
#include "HookEngine.h"
#include <android/input.h>
#include <android/looper.h>
#include <jni.h>

namespace TouchHook {

static AInputQueue* g_inputQueue = nullptr;
static bool g_menuVisible = false;

void InitTouchHook(AInputQueue* queue) {
    g_inputQueue = queue;
}

bool IsMenuVisible() {
    return g_menuVisible;
}

void SetMenuVisible(bool visible) {
    g_menuVisible = visible;
}

int32_t HandleTouchEvent(AInputEvent* event) {
    if (!g_inputQueue || AInputEvent_getType(event) != AINPUT_EVENT_TYPE_MOTION) {
        return 0;
    }

    if (g_menuVisible) {
        // Pass touch events to ImGui
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseSourceEvent(AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCH ?
            ImGuiMouseSource_Mouse : ImGuiMouseSource_Touch);
        
        float x = AMotionEvent_getX(event, 0);
        float y = AMotionEvent_getY(event, 0);
        io.AddMousePosEvent(x, y);
        
        int action = AMotionEvent_getAction(event);
        int button = action & AMOTION_EVENT_ACTION_MASK;
        io.AddMouseButtonEvent(0, button == AMOTION_EVENT_ACTION_DOWN || 
            button == AMOTION_EVENT_ACTION_MOVE);
        
        return 1;
    }

    return 0;
}

} // namespace TouchHook

=== END FILE ===
