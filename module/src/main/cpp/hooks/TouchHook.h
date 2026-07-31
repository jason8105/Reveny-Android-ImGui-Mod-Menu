#pragma once

class TouchHook {
public:
    static void init();
    static void injectTouch(int x, int y, int action);
    static bool isMenuOpen();
    
private:
    static bool menuOpen;
    static void* originalAInputQueue_getEvent;
};
=== END FILE ===
