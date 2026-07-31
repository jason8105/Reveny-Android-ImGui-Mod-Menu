#pragma once

class ImGuiHook {
public:
    static void Init();
    static void Cleanup();
    static void Render();
    static void HandleTouch(int x, int y, int action);
};
=== END FILE ===
