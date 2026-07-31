#include "ImGuiHook.h"
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <dlfcn.h>
#include <unistd.h>
#include <cstring>
#include <android/log.h>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static ImGuiIO* g_io = nullptr;
static bool g_initialized = false;

void ImGuiHook::Init() {
    if (g_initialized) return;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_io = ImGui::GetIO();
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    g_initialized = true;
    LOGD("ImGuiHook initialized");
}

void ImGuiHook::Cleanup() {
    if (!g_initialized) return;
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    
    g_initialized = false;
    LOGD("ImGuiHook cleanup");
}

void ImGuiHook::Render() {
    if (!g_initialized) return;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    
    ImGui::Begin("Reveny Menu", nullptr, ImGuiWindowFlags_NoCollapse);
    
    ImGui::Text("Reveny Mod Menu");
    ImGui::Separator();
    
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHook::HandleTouch(int x, int y, int action) {
    if (!g_initialized) return;
    
    g_io->AddMousePosEvent(static_cast<float>(x), static_cast<float>(y));
    g_io->AddMouseButtonEvent(0, action == 0);
}
=== END FILE ===
