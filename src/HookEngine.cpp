#include "HookEngine.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <fstream>
#include <sstream>
#include <cstring>

#define LOG_TAG "HookEngine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

std::vector<std::string> HookEngine::g_loadedModules;
bool HookEngine::g_initialized = false;

void HookEngine::Initialize() {
    if (g_initialized) return;
    
    LOGD("HookEngine initializing");
    
    // Read /proc/self/maps to get loaded modules
    std::ifstream maps("/proc/self/maps");
    std::string line;
    
    while (std::getline(maps, line)) {
        if (line.find(".so") != std::string::npos) {
            size_t start = line.find_last_of('/') + 1;
            size_t end = line.find('.');
            if (start != std::string::npos && end != std::string::npos && end > start) {
                std::string moduleName = line.substr(start, end - start);
                g_loadedModules.push_back(moduleName);
            }
        }
    }
    
    g_initialized = true;
    LOGD("HookEngine initialized with %zu modules", g_loadedModules.size());
}

void HookEngine::Cleanup() {
    g_loadedModules.clear();
    g_initialized = false;
}

void HookEngine::PltHookAllModules() {
    if (!g_initialized) {
        LOGE("HookEngine not initialized");
        return;
    }
    
    LOGD("PltHookAllModules called");
    
    // Hook common Android libraries
    const char* commonLibs[] = {
        "libc.so",
        "libandroid_runtime.so",
        "libbinder.so",
        "libui.so",
        "libgui.so",
        "libinput.so",
        "libEGL.so",
        "libGLESv2.so",
        "libGLESv3.so",
        "libOpenSLES.so",
        nullptr
    };
    
    for (int i = 0; commonLibs[i] != nullptr; i++) {
        void* handle = dlopen(commonLibs[i], RTLD_NOW);
        if (handle) {
            LOGD("Loaded %s", commonLibs[i]);
            dlclose(handle);
        }
    }
}

void HookEngine::HookFunction(const char* moduleName, const char* functionName, void* replacement) {
    if (!g_initialized) {
        LOGE("HookEngine not initialized");
        return;
    }
    
    void* handle = dlopen(moduleName, RTLD_NOW);
    if (!handle) {
        LOGE("Failed to load module %s: %s", moduleName, dlerror());
        return;
    }
    
    void* symbol = dlsym(handle, functionName);
    if (!symbol) {
        LOGE("Failed to find symbol %s in %s: %s", functionName, moduleName, dlerror());
        dlclose(handle);
        return;
    }
    
    LOGD("Hooking %s::%s at %p with %p", moduleName, functionName, symbol, replacement);
    
    // Apply hook (implementation depends on hooking method)
    dlclose(handle);
}

void* HookEngine::GetSymbol(const char* moduleName, const char* symbolName) {
    void* handle = dlopen(moduleName, RTLD_NOW);
    if (!handle) {
        LOGE("Failed to load module %s: %s", moduleName, dlerror());
        return nullptr;
    }
    
    void* symbol = dlsym(handle, symbolName);
    dlclose(handle);
    
    return symbol;
}

bool HookEngine::IsModuleLoaded(const char* moduleName) {
    for (const auto& mod : g_loadedModules) {
        if (mod == moduleName) return true;
    }
    return false;
}
=== END FILE ===
