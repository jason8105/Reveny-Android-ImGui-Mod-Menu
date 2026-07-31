#include "HookEngine.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "HookEngine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

JavaVM* HookEngine::g_javaVM = nullptr;
bool HookEngine::g_initialized = false;

void HookEngine::Initialize() {
    if (g_initialized) return;
    
    LOGD("HookEngine::Initialize()");
    
    // Hook all modules for Zygisk
    PltHookAllModules();
    
    g_initialized = true;
    LOGD("HookEngine initialized successfully");
}

void HookEngine::Shutdown() {
    if (!g_initialized) return;
    
    LOGD("HookEngine::Shutdown()");
    
    g_initialized = false;
    g_javaVM = nullptr;
}

void HookEngine::SetJavaVM(JavaVM* vm) {
    g_javaVM = vm;
}

JavaVM* HookEngine::GetJavaVM() {
    return g_javaVM;
}

void HookEngine::PltHookAllModules() {
    LOGD("Hooking all loaded modules");
    
    // Hook common graphics libraries
    const char* graphicsLibs[] = {
        "libEGL.so",
        "libGLESv2.so",
        "libGLESv3.so",
        "libvulkan.so",
        nullptr
    };
    
    for (const char* lib : graphicsLibs) {
        void* handle = dlopen(lib, RTLD_NOW);
        if (handle) {
            LOGD("Found library: %s", lib);
            dlclose(handle);
        }
    }
}

=== END FILE ===
