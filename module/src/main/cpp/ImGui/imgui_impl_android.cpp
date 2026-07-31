#include "imgui_impl_android.h"
#include "imgui.h"
#include <android/log.h>

#define LOG_TAG "RevenyAndroid"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void ImGui_ImplAndroid_Init(void* window) {
    LOGD("ImGui Android backend initialized");
}

void ImGui_ImplAndroid_NewFrame() {
    // Android-specific input handling
}

void ImGui_ImplAndroid_Shutdown() {
    LOGD("ImGui Android backend shutdown");
}
=== END FILE ===
