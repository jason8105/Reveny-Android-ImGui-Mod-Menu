#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ImGui_ImplAndroid_Init(void* window);
void ImGui_ImplAndroid_Shutdown();
void ImGui_ImplAndroid_NewFrame();
void ImGui_ImplAndroid_Render();

#ifdef __cplusplus
}
#endif
=== END FILE ===
