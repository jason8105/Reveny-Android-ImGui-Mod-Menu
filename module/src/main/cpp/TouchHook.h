#pragma once

class TouchHook {
public:
    static void Initialize();
    static void SetMenuVisible(bool visible);
    static void Cleanup();
    static bool IsMenuVisible();
};
=== END FILE ===
