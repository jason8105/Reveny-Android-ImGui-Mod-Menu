#pragma once

#include <dlfcn.h>
#include <string>
#include <vector>

class HookEngine {
public:
    static void init();
    static void hookEGLSwapBuffers();
    static void hookVulkanSwapchain();
    static void hookAInputQueue_getEvent();
    
private:
    static void* getModuleHandle(const char* moduleName);
    static void* findSymbol(void* handle, const char* symbol);
};
=== END FILE ===
