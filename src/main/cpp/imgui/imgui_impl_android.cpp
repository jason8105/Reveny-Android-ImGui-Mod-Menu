#include "imgui_impl_android.h"
#include <android/looper.h>
#include <android/input.h>
#include <android/native_window.h>
#include <android/log.h>

#define LOG_TAG "ImGuiAndroid"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static struct {
    ANativeWindow* window;
    int width;
    int height;
    int displayWidth;
    int displayHeight;
} g_Android;

bool ImGui_ImplAndroid_Init(void* app) {
    LOGD("ImGui Android initialized");
    return true;
}

void ImGui_ImplAndroid_Shutdown() {
    LOGD("ImGui Android shutdown");
}

void ImGui_ImplAndroid_NewFrame() {
    ImGuiIO& io = ImGui::GetIO();
    
    if (g_Android.window) {
        ANativeWindow_setBuffersGeometry(g_Android.window, 0, 0, 0);
    }
    
    io.DisplaySize = ImVec2((float)g_Android.width, (float)g_Android.height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

void ImGui_ImplAndroid_ProcessEvent(const AInputEvent* e) {
    if (e == nullptr) return;
    
    int type = AInputEvent_getType(e);
    
    if (type == AINPUT_EVENT_TYPE_MOTION) {
        int action = AMotionEvent_getAction(e);
        int pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        int pointerId = (action & AMOTION_EVENT_ACTION_POINTER_ID_MASK) >> AMOTION_EVENT_ACTION_POINTER_ID_SHIFT;
        
        float x = AMotionEvent_getX(e, pointerIndex);
        float y = AMotionEvent_getY(e, pointerIndex);
        
        ImGuiIO& io = ImGui::GetIO();
        
        switch (action & AMOTION_EVENT_ACTION_MASK) {
        case AMOTION_EVENT_ACTION_DOWN:
        case AMOTION_EVENT_ACTION_POINTER_DOWN:
            io.AddMousePosEvent(x, y);
            io.AddMouseButtonEvent(0, true);
            break;
        case AMOTION_EVENT_ACTION_UP:
        case AMOTION_EVENT_ACTION_POINTER_UP:
            io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
            io.AddMouseButtonEvent(0, false);
            break;
        case AMOTION_EVENT_ACTION_MOVE:
            io.AddMousePosEvent(x, y);
            break;
        }
    }
}

=== END FILE ===
