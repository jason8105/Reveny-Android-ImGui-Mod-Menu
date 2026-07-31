#pragma once

class ImGuiHook {
public:
    static void Initialize();
    static void Shutdown();
    static void Render();
    static void OnSwapBuffers();
    static void OnEGLInit();

private:
    static bool g_initialized;
    static bool g_rendering;
};

=== END FILE ===
