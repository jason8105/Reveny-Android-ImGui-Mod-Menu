#include "HookEngine.h"
#include <dlfcn.h>
#include <cstring>
#include <android/log.h>

#define LOG_TAG "RevenyHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void HookEngine::init() {
    LOGD("HookEngine initialized");
    hookEGLSwapBuffers();
    hookAInputQueue_getEvent();
}

void* HookEngine::getModuleHandle(const char* moduleName) {
    void* handle = dlopen(moduleName, RTLD_NOW);
    if (!handle) {
        LOGD("Failed to load module: %s", dlerror());
    }
    return handle;
}

void* HookEngine::findSymbol(void* handle, const char* symbol) {
    if (!handle) return nullptr;
    return dlsym(handle, symbol);
}

void HookEngine::hookEGLSwapBuffers() {
    void* eglHandle = getModuleHandle("libEGL.so");
    if (!eglHandle) {
        LOGD("Failed to load libEGL.so");
        return;
    }
    
    void* eglSwapBuffers = findSymbol(eglHandle, "eglSwapBuffers");
    if (!eglSwapBuffers) {
        LOGD("Failed to find eglSwapBuffers");
        return;
    }
    
    LOGD("EGL swap buffers hook found at: %p", eglSwapBuffers);
}

void HookEngine::hookVulkanSwapchain() {
    void* vulkanHandle = getModuleHandle("libvulkan.so");
    if (!vulkanHandle) {
        LOGD("Failed to load libvulkan.so");
        return;
    }
    
    void* vkQueuePresentKHR = findSymbol(vulkanHandle, "vkQueuePresentKHR");
    if (!vkQueuePresentKHR) {
        LOGD("Failed to find vkQueuePresentKHR");
        return;
    }
    
    LOGD("Vulkan swapchain hook found at: %p", vkQueuePresentKHR);
}

void HookEngine::hookAInputQueue_getEvent() {
    void* inputHandle = getModuleHandle("libandroid.so");
    if (!inputHandle) {
        LOGD("Failed to load libandroid.so");
        return;
    }
    
    void* getInputEvent = findSymbol(inputHandle, "_Z18AInputQueue_getEventP10AInputQueueP10AInputEvent");
    if (!getInputEvent) {
        LOGD("Failed to find AInputQueue_getEvent");
        return;
    }
    
    LOGD("Input queue hook found at: %p", getInputEvent);
}
=== END FILE ===
