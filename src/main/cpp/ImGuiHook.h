#pragma once

#include <jni.h>

class ImGuiHook {
public:
    static void init();
    static void cleanup();
    
    static void renderOverlay();
    static void handleTouchInput(int x, int y, int action);
    
private:
    static bool initialized;
    static void* originalEglSwapBuffers;
    static void* originalVulkanSwapchainPresent;
    
    static void hookEglSwapBuffers(void* display, void* surface);
    static void hookVulkanSwapchainPresent(void* device, void* queue, void* presentInfo);
};
