#pragma once

#include <string>

class ImGuiRenderer {
public:
    static void init();
    static void cleanup();
    static void render();
    static void onSwapBuffers();
};
=== END FILE ===
