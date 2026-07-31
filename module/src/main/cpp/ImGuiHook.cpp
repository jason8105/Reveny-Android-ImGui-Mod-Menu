#include "ImGuiHook.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <thread>
#include <chrono>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace ImGuiHook {
    void Init() {
        LOGD("ImGui hook initialized");
    }
    
    void Render() {
        LOGD("Rendering ImGui");
    }
    
    void SwapBuffers() {
        LOGD("Swapping buffers");
    }
}
=== END FILE ===
