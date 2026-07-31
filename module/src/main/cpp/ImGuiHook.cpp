#include "ImGuiHook.h"
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

namespace ImGuiHook {

void Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}

void Render() {
    ImGui::SetNextWindowPos(ImVec2(100, 100));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    
    ImGui::Begin("Mod Menu");
    ImGui::Text("Reveny Mod Menu");
    ImGui::End();
}

}
=== END FILE ===
