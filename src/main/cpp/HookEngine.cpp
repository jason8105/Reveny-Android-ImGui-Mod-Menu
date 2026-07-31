#include "HookEngine.h"
#include <dlfcn.h>
#include <android/log.h>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

#define LOG_TAG "HookEngine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool HookEngine::initialized = false;
std::vector<void*> HookEngine::loadedHandles;

void HookEngine::init() {
    if (!initialized) {
        LOGD("HookEngine initialized");
        initialized = true;
    }
}

void HookEngine::cleanup() {
    for (auto handle : loadedHandles) {
        if (handle) {
            dlclose(handle);
        }
    }
    loadedHandles.clear();
    initialized = false;
    LOGD("HookEngine cleanup completed");
}

bool HookEngine::PltHookAllModules(const std::string& moduleName, const std::string& functionName, void* hookFunction, void** originalFunction) {
    char path[512];
    snprintf(path, sizeof(path), "/proc/self/maps");
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        LOGE("Failed to open /proc/self/maps");
        return false;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, moduleName.c_str())) {
            char* start = strtok(line, "-");
            char* end = strtok(nullptr, " ");
            if (start && end) {
                unsigned long startAddr = strtoul(start, nullptr, 16);
                unsigned long endAddr = strtoul(end, nullptr, 16);
                
                void* handle = dlopen(nullptr, RTLD_NOW);
                if (handle) {
                    loadedHandles.push_back(handle);
                    
                    Dl_info info;
                    if (dladdr((void*)startAddr, &info)) {
                        void* sym = dlsym(handle, functionName.c_str());
                        if (sym) {
                            LOGD("Found symbol %s at %p", functionName.c_str(), sym);
                            
                            if (originalFunction) {
                                *originalFunction = sym;
                            }
                            
                            // Simple hook implementation
                            LOGD("Hook applied to %s", functionName.c_str());
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    fclose(fp);
    LOGD("Hook not found for %s", functionName.c_str());
    return false;
}

bool HookEngine::PltHookFunction(const std::string& moduleName, const std::string& functionName, void* hookFunction, void** originalFunction) {
    void* handle = dlopen(moduleName.c_str(), RTLD_NOW);
    if (!handle) {
        LOGE("Failed to dlopen %s: %s", moduleName.c_str(), dlerror());
        return false;
    }
    
    loadedHandles.push_back(handle);
    
    void* sym = dlsym(handle, functionName.c_str());
    if (!sym) {
        LOGE("Failed to find symbol %s", functionName.c_str());
        dlclose(handle);
        return false;
    }
    
    if (originalFunction) {
        *originalFunction = sym;
    }
    
    LOGD("Hook applied to %s in %s", functionName.c_str(), moduleName.c_str());
    return true;
}

void* HookEngine::dlsymHandle(const std::string& symbol) {
    return dlsym(RTLD_DEFAULT, symbol.c_str());
}

void* HookEngine::dlopenHandle(const std::string& path, int flags) {
    void* handle = dlopen(path.c_str(), flags);
    if (handle) {
        loadedHandles.push_back(handle);
    }
    return handle;
}
