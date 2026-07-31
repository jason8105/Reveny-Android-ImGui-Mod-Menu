#include "imgui_renderer.h"
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window_jni.h>
#include <android/log.h>

#define LOG_TAG "ImGuiRenderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, LOG__VA_ARGS__)

static ImGuiIO* g_io = nullptr;
static bool g_initialized = false;
static ANativeWindow* g_window = nullptr;

void ImGuiRenderer::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_io = ImGui::GetIO();
    g_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    g_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.GrabRounding = 4.0f;

    g_initialized = true;
}

void ImGuiRenderer::cleanup() {
    if (g_io) {
        ImGui::DestroyContext();
        g_io = nullptr;
    }
    g_initialized = false;
}

void ImGuiRenderer::render() {
    if (!g_initialized) return;

    ImGui_ImplAndroid_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(300, 400));

    ImGui::Begin("Reveny Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Mod Menu v1.0");
    ImGui::Separator();

    if (ImGui::Button("Toggle Menu")) {
        g_io->WantCaptureMouse = !g_io->WantCaptureMouse;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiRenderer::onSwapBuffers() {
    render();
}
=== END FILE ===
