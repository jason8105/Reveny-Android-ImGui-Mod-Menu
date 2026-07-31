#include "ImGuiHook.h"
#include "HookEngine.h"
#include "TouchHook.h"
#include <jni.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool ImGuiHook::g_initialized = false;
bool ImGuiHook::g_rendering = false;

void ImGuiHook::Initialize() {
    if (g_initialized) return;
    
    LOGD("ImGuiHook::Initialize()");
    
    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    
    // Setup Platform/Renderer backends
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    // Setup style
    ImGui::StyleColorsDark();
    
    g_initialized = true;
    LOGD("ImGuiHook initialized successfully");
}

void ImGuiHook::Shutdown() {
    if (!g_initialized) return;
    
    LOGD("ImGuiHook::Shutdown()");
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    
    g_initialized = false;
}

void ImGuiHook::Render() {
    if (!g_initialized || !g_rendering) return;
    
    ImGuiIO& io = ImGui::GetIO();
    
    // Handle touch input from TouchHook
    if (TouchHook::IsMenuVisible()) {
        io.WantCaptureMouse = true;
        io.WantCaptureKeyboard = true;
    }
    
    // Begin main window
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Game Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);
    
    // Menu content
    ImGui::Text("ImGui Hook Active");
    ImGui::Separator();
    
    if (ImGui::Button("Toggle Menu")) {
        TouchHook::SetMenuVisible(!TouchHook::IsMenuVisible());
    }
    
    ImGui::Checkbox("Enable Touch", &TouchHook::IsTouchEnabled());
    
    ImGui::End();
    
    // Render ImGui
    ImGui::Render();
    
    // Swap buffers
    eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentContext());
}

void ImGuiHook::OnSwapBuffers() {
    if (!g_initialized) return;
    
    g_rendering = true;
    Render();
    g_rendering = false;
}

void ImGuiHook::OnEGLInit() {
    if (g_initialized) return;
    
    Initialize();
}

=== END FILE ===
