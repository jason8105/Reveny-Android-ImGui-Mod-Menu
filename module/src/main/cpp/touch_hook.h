#pragma once

class TouchHook {
public:
    static void init();
    static void cleanup();
    static bool isMenuOpen();
    static void injectTouch(int x, int y, int action);
};
=== END FILE ===
