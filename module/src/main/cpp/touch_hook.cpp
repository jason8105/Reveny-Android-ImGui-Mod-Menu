#include "touch_hook.h"
#include "imgui_renderer.h"
#include <android/input.h>
#include <android/looper.h>
#include <sys/system_properties.h>

static bool g_menu_open = false;
static bool g_touch_hooked = false;

void TouchHook::init() {
    g_touch_hooked = true;
}

void TouchHook::cleanup() {
    g_touch_hooked = false;
}

bool TouchHook::isMenuOpen() {
    return g_menu_open;
}

void TouchHook::injectTouch(int x, int y, int action) {
    if (g_menu_open) {
        // Inject touch to ImGui
    }
}
=== END FILE ===
