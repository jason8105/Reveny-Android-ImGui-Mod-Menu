#pragma once

// ImGui Context and Window Management
namespace ImGui {
    void CreateContext(ImFontAtlas* shared_font_atlas = nullptr);
    void DestroyContext(ImGuiContext* ctx = nullptr);
    ImGuiContext* GetCurrentContext();
    void SetCurrentContext(ImGuiContext* ctx);
    
    void NewFrame();
    void Render();
    ImDrawData* GetDrawData();
    
    // Window Position and Size
    void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0));
    void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    void SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = nullptr, void* custom_callback_data = nullptr);
    
    // Main Menu
    void ShowDemoWindow(bool* p_open = nullptr);
    void ShowStyleEditor(ImGuiStyle* ref = nullptr);
    void ShowMetricsWindow(bool* p_open = nullptr);
}
=== END FILE ===
