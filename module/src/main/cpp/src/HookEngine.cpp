#include "HookEngine.h"
#include <dlfcn.h>
#include <cstring>
#include <vector>
#include <string>

namespace HookEngine {

void* dlsym_safe(const char* symbol) {
    void* handle = dlopen("libandroid_runtime.so", RTLD_NOW);
    if (!handle) {
        handle = dlopen("libart.so", RTLD_NOW);
    }
    if (!handle) {
        handle = dlopen("libart-compiler.so", RTLD_NOW);
    }
    if (!handle) {
        handle = dlopen("libart.so", RTLD_NOW);
    }
    if (!handle) {
        return nullptr;
    }
    void* sym = dlsym(handle, symbol);
    dlclose(handle);
    return sym;
}

bool HookEngine::PltHookAllModules(const char* symbol, void* replacement, void** original) {
    Dl_info info;
    if (dladdr(replacement, &info) == 0) {
        return false;
    }
    
    std::vector<std::string> modules;
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return false;
    
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, ".so")) {
            char* start = strchr(line, '/');
            if (start) {
                char* end = strchr(start, ' ');
                if (end) {
                    *end = '\0';
                    modules.push_back(start);
                }
            }
        }
    }
    fclose(fp);
    
    for (const auto& module : modules) {
        void* handle = dlopen(module.c_str(), RTLD_NOW);
        if (!handle) continue;
        
        void* sym = dlsym(handle, symbol);
        if (sym) {
            *original = sym;
            dlclose(handle);
            return true;
        }
        dlclose(handle);
    }
    
    return false;
}

}
=== END FILE ===
