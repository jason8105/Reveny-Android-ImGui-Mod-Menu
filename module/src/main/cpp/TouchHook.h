#pragma once

class TouchHook {
public:
    static void Init();
    static void Cleanup();
    static void InjectTouch(int x, int y, int action);
};
=== END FILE ===
