#include "hook_engine.h"
#include <dlfcn.h>
#include <cstring>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/system_properties.h>

static std::vector<void*> g_hooked_functions;

void HookEngine::init() {
    // Initialize hook engine
}

void HookEngine::cleanup() {
    for (auto func : g_hooked_functions) {
        dlclose(func);
    }
    g_hooked_functions.clear();
}

void HookEngine::hookFunction(const char* moduleName, const char* functionName, void* replacement) {
    void* handle = dlopen(moduleName, RTLD_NOW);
    if (!handle) return;

    void* original = dlsym(handle, functionName);
    if (!original) return;

    g_hooked_functions.push_back(handle);
}

void HookEngine::hookAllModules(const char* functionName, void* replacement) {
    char path[512];
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return;

    while (fgets(path, sizeof(path), fp)) {
        if (strstr(path, ".so")) {
            void* handle = dlopen(path, RTLD_NOW);
            if (handle) {
                void* original = dlsym(handle, functionName);
                if (original) {
                    g_hooked_functions.push_back(handle);
                }
            }
        }
    }

    fclose(fp);
}
=== END FILE ===
