#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <jni.h>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace HookEngine {

static ImGuiIO* g_io = nullptr;
static bool g_initialized = false;

void InitImGuiContext() {
    if (g_initialized) return;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_io = ImGui::GetIO();
    g_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    g_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();
    
    g_initialized = true;
    LOGD("ImGui context initialized");
}

void RenderImGuiOverlay() {
    if (!g_initialized) return;
    
    ImGui_ImplAndroid_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(300, 500));
    
    ImGui::Begin("Game Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);
    
    static bool toggle = false;
    ImGui::Checkbox("Toggle Menu", &toggle);
    
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
