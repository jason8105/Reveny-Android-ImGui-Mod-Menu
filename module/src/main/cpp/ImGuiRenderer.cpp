#include "ImGuiRenderer.h"
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <cstring>

namespace ImGuiRenderer {

static ImGuiIO* g_io = nullptr;
static bool g_initialized = false;

bool ImGuiRenderer::Initialize() {
    if (g_initialized) return true;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_io = ImGui::GetIO();
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    g_initialized = true;
    return true;
}

void ImGuiRenderer::Render() {
    if (!g_initialized) return;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    
    // Your menu rendering here
    // ImGui::ShowDemoWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiRenderer::SetWindowPos(float x, float y) {
    if (g_io) {
        ImGui::SetNextWindowPos(ImVec2(x, y));
    }
}

void ImGuiRenderer::SetWindowSize(float width, float height) {
    if (g_io) {
        ImGui::SetNextWindowSize(ImVec2(width, height));
    }
}

void ImGuiRenderer::Shutdown() {
    if (g_initialized) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplAndroid_Shutdown();
        ImGui::DestroyContext();
        g_initialized = false;
    }
}

} // namespace ImGuiRenderer
=== END FILE ===
