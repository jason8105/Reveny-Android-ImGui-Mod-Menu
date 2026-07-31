#include "imgui_impl_android.h"
#include <android/log.h>

#define LOG_TAG "ImGuiAndroid"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void ImGui_ImplAndroid_Init(void* window) {
    LOGD("ImGui Android initialized");
}

void ImGui_ImplAndroid_Shutdown() {
    LOGD("ImGui Android shutdown");
}

void ImGui_ImplAndroid_NewFrame() {
    LOGD("ImGui Android new frame");
}

void ImGui_ImplAndroid_Render() {
    LOGD("ImGui Android render");
}
=== END FILE ===
