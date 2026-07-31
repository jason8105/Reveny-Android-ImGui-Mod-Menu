#pragma once

#include "imgui.h"

IMGUI_IMPL_API bool     ImGui_ImplAndroid_Init(void* app);
IMGUI_IMPL_API void     ImGui_ImplAndroid_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplAndroid_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplAndroid_ProcessEvent(const AInputEvent* e);

=== END FILE ===
