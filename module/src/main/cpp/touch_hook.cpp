#include "touch_hook.h"
#include "imgui_impl.h"

bool TouchHook::g_menu_open = false;
void* TouchHook::g_original_input_queue = nullptr;

void TouchHook::init() {
    g_menu_open = false;
    g_original_input_queue = nullptr;
}

void TouchHook::deinit() {
    g_menu_open = false;
    g_original_input_queue = nullptr;
}

void TouchHook::injectTouch(int x, int y, int action) {
    // Inject touch event for ImGui menu interaction
    ImGuiImpl::handleTouch(x, y, action);
}

bool TouchHook::isMenuOpen() {
    return g_menu_open;
}
=== END FILE ===
