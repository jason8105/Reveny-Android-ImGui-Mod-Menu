#include "ImGuiHook.h"
#include "TouchHook.h"
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <thread>
#include <chrono>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static bool g_initialized = false;
static ImGuiContext* g_context = nullptr;

void ImGuiHook::init() {
    if (g_initialized) return;
    g_initialized = true;

    LOGD("ImGuiHook initialized");

    IMGUI_CHECKVERSION();
    g_context = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_context);

    ImGui::StyleColorsDark();

    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    std::thread renderThread([]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            render();
        }
    });

    renderThread.detach();
}

void ImGuiHook::cleanup() {
    if (!g_initialized) return;
    g_initialized = false;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext(g_context);

    LOGD("ImGuiHook cleanup");
}

void ImGuiHook::render() {
    if (!g_initialized) return;

    if (TouchHook::isMenuOpen()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 500));

        ImGui::Begin("Reveny Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Reveny Mod Menu");
        ImGui::Separator();

        ImGui::Checkbox("Menu Enabled", &g_menuOpen);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
=== END FILE ===
