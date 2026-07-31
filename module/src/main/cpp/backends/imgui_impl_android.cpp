#include "imgui_impl_android.h"
#include <android/native_window.h>
#include <android/looper.h>
#include <android/queue.h>
#include <unistd.h>
#include <cstring>
#include <android/log.h>

#define LOG_TAG "ImGuiAndroid"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static void* g_native_app = nullptr;

void ImGui_ImplAndroid_Init(void* native_app) {
    g_native_app = native_app;
    LOGD("ImGui Android backend initialized");
}

void ImGui_ImplAndroid_Shutdown() {
    g_native_app = nullptr;
    LOGD("ImGui Android backend shutdown");
}

void ImGui_ImplAndroid_NewFrame() {
    // Android-specific input handling
}
=== END FILE ===
