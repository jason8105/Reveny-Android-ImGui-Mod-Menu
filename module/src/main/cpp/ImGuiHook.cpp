#include "ImGuiHook.h"
#include "HookEngine.h"
#include "TouchHook.h"
#include <imgui.h>
#include <backends/imgui_impl_android.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include <android/log.h>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace ImGuiHook {
    void Render() {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 500));
        ImGui::Begin("Reveny Mod Menu");

        if (ImGui::Button("Toggle Menu")) {
            TouchHook::SetMenuVisible(!TouchHook::IsMenuVisible());
        }

        ImGui::End();
    }
}
=== END FILE ===
