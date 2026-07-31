#include "ImGuiRenderer.h"
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

namespace ImGuiRenderer {

void Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}

void Render() {
    ImGui::NewFrame();
    
    ImGui::SetNextWindowPos(ImVec2(100, 100));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    
    ImGui::Begin("Reveny Mod Menu");
    ImGui::Text("Mod Menu Loaded");
    ImGui::End();
    
    ImGui::Render();
}

void Shutdown() {
    ImGui::DestroyContext();
}

} // namespace ImGuiRenderer
=== END FILE ===
