#pragma once

#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

class ImGuiImpl {
public:
    static void init();
    static void deinit();
    
    static void render();
    static void handleTouch(int x, int y, int action);
    static void setNextWindowPos(float x, float y);
    static void setNextWindowSize(float width, float height);
    
private:
    static bool g_initialized;
    static ImGuiContext* g_context;
};
=== END FILE ===
