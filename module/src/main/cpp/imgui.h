#pragma once

// ImGui header placeholder - actual ImGui files should be included via submodule
// This file exists to prevent compilation errors if ImGui is not properly linked

namespace ImGui {
    void CreateContext(void* impl = nullptr);
    void DestroyContext(void* context = nullptr);
    void NewFrame();
    void Render();
    void End();
    void Begin(const char* name, bool* p_open = nullptr, int flags = 0);
    void Text(const char* fmt, ...);
    void Separator();
    void StyleColorsDark();
    void SetNextWindowPos(const ImVec2& pos);
    void SetNextWindowSize(const ImVec2& size);
    void* GetDrawData();
    struct IO {
        void AddMousePosEvent(float x, float y);
        void AddMouseButtonEvent(int button, bool down);
    };
    IO* GetIO();
    bool GetIO();
}

struct ImVec2 {
    float x, y;
    ImVec2(float _x, float _y) : x(_x), y(_y) {}
};
=== END FILE ===
