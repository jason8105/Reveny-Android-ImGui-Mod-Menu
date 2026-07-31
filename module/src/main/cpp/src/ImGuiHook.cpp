#include "ImGuiHook.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>

#define LOG_TAG "RevenyImGui"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace ImGuiHook {

static bool initialized = false;
static ImGuiContext* imguiContext = nullptr;

void InitImGui() {
    if (initialized) return;
    
    IMGUI_CHECKVERSION();
    imguiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(imguiContext);
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    
    ImGui::StyleColorsDark();
    
    initialized = true;
    LOGI("ImGui initialized successfully");
}

void RenderImGui() {
    if (!initialized || !imguiContext) return;
    
    ImGui::NewFrame();
    
    static bool showDemo = true;
    if (showDemo) {
        ImGui::ShowDemoWindow(&showDemo);
    }
    
    ImGui::Render();
}

void CleanupImGui() {
    if (imguiContext) {
        ImGui::DestroyContext(imguiContext);
        imguiContext = nullptr;
    }
    initialized = false;
}

bool IsInitialized() {
    return initialized;
}

}
=== END FILE ===
