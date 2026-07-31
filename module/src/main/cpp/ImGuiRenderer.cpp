#include "ImGuiRenderer.h"
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"

namespace ImGuiRenderer {
    void Render() {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 400));
        
        ImGui::Begin("Mod Menu");
        ImGui::Text("Reveny Mod Menu");
        ImGui::End();
    }
}
=== END FILE ===
