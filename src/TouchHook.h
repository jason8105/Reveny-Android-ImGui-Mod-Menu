#pragma once

class TouchHook {
public:
    static void Initialize();
    static void Shutdown();
    static void HookInputQueue();
    static void SetMenuVisible(bool visible);
    static void SetTouchEnabled(bool enabled);
    static bool IsMenuVisible();
    static bool IsTouchEnabled();

private:
    static bool g_initialized;
    static bool g_touchEnabled;
    static bool g_menuVisible;
};

=== END FILE ===
