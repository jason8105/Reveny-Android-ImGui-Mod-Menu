#pragma once

#define IMGUI_VERSION "1.90.0"

#ifdef __cplusplus
extern "C" {
#endif

// Main API
typedef struct ImGuiIO ImGuiIO;

struct ImGuiIO {
    // Add settings
};

void ImGui_Init();
void ImGui_Shutdown();
void ImGui_NewFrame();
void ImGui_Render();

#ifdef __cplusplus
}
#endif
=== END FILE ===
