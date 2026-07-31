#pragma once

class TouchHook {
public:
    static void init();
    static void cleanup();
    static bool isMenuOpen();
    static void setMenuOpen(bool open);
};
=== END FILE ===
