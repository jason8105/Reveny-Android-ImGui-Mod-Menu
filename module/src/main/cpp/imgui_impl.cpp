#include "imgui_impl.h"
#include "touch_hook.h"
#include <android/native_window_jni.h>
#include <EGL/egl.h>

bool ImGuiImpl::g_initialized = false;
ImGuiContext* ImGuiImpl::g_context = nullptr;

void ImGuiImpl::init() {
    if (g_initialized) return;
    
    IMGUI_CHECKVERSION();
    g_context = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_context);
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    g_initialized = true;
}

void ImGuiImpl::deinit() {
    if (!g_initialized) return;
    
    ImGui::DestroyContext(g_context);
    g_context = nullptr;
    g_initialized = false;
}

void ImGuiImpl::render() {
    if (!g_initialized) return;
    
    ImGui::Render();
}

void ImGuiImpl::handleTouch(int x, int y, int action) {
    if (!g_initialized) return;
    
    ImGuiIO& io = ImGui::GetIO();
    
    switch (action) {
        case 0: // ACTION_DOWN
            io.AddMouseButtonEvent(0, true);
            io.AddMousePosEvent(x, y);
            break;
        case 1: // ACTION_UP
            io.AddMouseButtonEvent(0, false);
            break;
        case 2: // ACTION_MOVE
            io.AddMousePosEvent(x, y);
            break;
    }
}

void ImGuiImpl::setNextWindowPos(float x, float y) {
    if (!g_initialized) return;
    ImGui::SetNextWindowPos(ImVec2(x, y));
}

void ImGuiImpl::setNextWindowSize(float width, float height) {
    if (!g_initialized) return;
    ImGui::SetNextWindowSize(ImVec2(width, height));
}
=== END FILE ===
