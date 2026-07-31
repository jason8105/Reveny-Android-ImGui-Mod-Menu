#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>
#include <GLES3/gl3.h>

void render_loop() {
    ImGui::SetNextWindowPos(ImVec2(100, 100));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    
    ImGui::Begin("Reveny Mod Menu");
    ImGui::Text("Mod Menu Loaded");
    ImGui::End();
}

=== END FILE ===
