#include "ImGuiHook.h"
#include "HookEngine.h"
#include "TouchHook.h"
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <cstring>

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool ImGuiHook::initialized = false;
void* ImGuiHook::originalEglSwapBuffers = nullptr;
void* ImGuiHook::originalVulkanSwapchainPresent = nullptr;

// ImGui includes
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"

void ImGuiHook::init() {
    if (initialized) {
        LOGD("ImGuiHook already initialized");
        return;
    }
    
    LOGD("Initializing ImGuiHook...");
    
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    // Setup Platform/Renderer backends
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    // Setup style
    ImGui::StyleColorsDark();
    
    // Hook graphics functions
    HookEngine::PltHookFunction("libEGL.so", "eglSwapBuffers",
        reinterpret_cast<void*>(hookEglSwapBuffers), &originalEglSwapBuffers);
    
    initialized = true;
    LOGD("ImGuiHook initialized successfully");
}

void ImGuiHook::cleanup() {
    if (!initialized) {
        return;
    }
    
    LOGD("Cleaning up ImGuiHook...");
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    
    initialized = false;
    LOGD("ImGuiHook cleanup completed");
}

void ImGuiHook::renderOverlay() {
    if (!initialized) {
        return;
    }
    
    ImGuiIO& io = ImGui::GetIO();
    
    // Window positioning - fixed to avoid compilation errors
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(300, 400));
    
    ImGui::Begin("Game Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);
    
    // Menu content
    if (ImGui::Button("Toggle Menu")) {
        TouchHook::setMenuOpen(!TouchHook::isMenuOpen());
    }
    
    if (ImGui::Button("Save State")) {
        LOGD("State saved");
    }
    
    if (ImGui::Button("Load State")) {
        LOGD("State loaded");
    }
    
    ImGui::End();
    
    ImGui::Render();
}

void ImGuiHook::handleTouchInput(int x, int y, int action) {
    if (!initialized) {
        return;
    }
    
    ImGuiIO& io = ImGui::GetIO();
    
    if (action == 0) { // ACTION_DOWN
        io.AddMousePosEvent(static_cast<float>(x), static_cast<float>(y));
        io.AddMouseButtonEvent(0, true);
    } else if (action == 1) { // ACTION_UP
        io.AddMousePosEvent(static_cast<float>(x), static_cast<float>(y));
        io.AddMouseButtonEvent(0, false);
    } else if (action == 2) { // ACTION_MOVE
        io.AddMousePosEvent(static_cast<float>(x), static_cast<float>(y));
    }
}

void ImGuiHook::hookEglSwapBuffers(void* display, void* surface) {
    if (originalEglSwapBuffers) {
        // Render ImGui before swap
        if (!TouchHook::isMenuOpen()) {
            renderOverlay();
        }
        
        // Call original function
        reinterpret_cast<void(*)(void*, void*)>(originalEglSwapBuffers)(display, surface);
    }
}

void ImGuiHook::hookVulkanSwapchainPresent(void* device, void* queue, void* presentInfo) {
    if (originalVulkanSwapchainPresent) {
        renderOverlay();
        reinterpret_cast<void(*)(void*, void*, void*)>(originalVulkanSwapchainPresent)(device, queue, presentInfo);
    }
}
