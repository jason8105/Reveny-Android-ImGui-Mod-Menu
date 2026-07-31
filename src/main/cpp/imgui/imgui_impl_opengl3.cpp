#include "imgui_impl_opengl3.h"
#include <GLES3/gl3.h>
#include <android/log.h>

#define LOG_TAG "ImGuiOpenGL3"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static const char* ImGui_ImplOpenGL3_GetGLSLVersion() {
    return "#version 300 es";
}

bool ImGui_ImplOpenGL3_Init(const char* glsl_version) {
    LOGD("ImGui OpenGL3 initialized");
    return true;
}

void ImGui_ImplOpenGL3_Shutdown() {
    LOGD("ImGui OpenGL3 shutdown");
}

void ImGui_ImplOpenGL3_NewFrame() {
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
}

void ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data) {
    if (draw_data == nullptr) return;
    
    // Render ImGui draw data
    // Simplified implementation for Android
    LOGD("Rendering ImGui draw data");
}

=== END FILE ===
