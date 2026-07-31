#pragma once

class TouchHook {
public:
    static void init();
    static void deinit();
    
    static void injectTouch(int x, int y, int action);
    static bool isMenuOpen();
    
private:
    static bool g_menu_open;
    static void* g_original_input_queue;
};
=== END FILE ===
