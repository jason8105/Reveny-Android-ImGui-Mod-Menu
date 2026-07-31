#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

void ImGuiHook::RenderOverlay() {
    ImGui::SetNextWindowPos(ImVec2(100, 100));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    ImGui::Begin("Mod Menu");
    ImGui::End();
}
=== END FILE ===
