#include "imgui.h"
#include "imgui_impl_android.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "ImGuiAndroid"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static ANativeWindow* g_window = nullptr;

void ImGui_ImplAndroid_Init(void* window) {
    g_window = (ANativeWindow*)window;
    LOGD("ImGui Android initialized with window: %p", window);
}

void ImGui_ImplAndroid_Shutdown() {
    g_window = nullptr;
    LOGD("ImGui Android shutdown");
}

void ImGui_ImplAndroid_NewFrame() {
    if (!g_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    
    int width = ANativeWindow_getWidth(g_window);
    int height = ANativeWindow_getHeight(g_window);
    
    io.DisplaySize = ImVec2((float)width, (float)height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    
    LOGD("New frame: %dx%d", width, height);
}

void ImGui_ImplAndroid_Render() {
    // Render function handled by backend
}
=== END FILE ===
