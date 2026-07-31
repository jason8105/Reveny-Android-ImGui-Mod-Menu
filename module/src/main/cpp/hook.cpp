#include "hook.h"
#include <dlfcn.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::string> HookEngine::g_loaded_libraries;

void HookEngine::init() {
    g_loaded_libraries.clear();
}

void HookEngine::deinit() {
    g_loaded_libraries.clear();
}

bool HookEngine::hookFunction(const char* library, const char* symbol, void* replacement, void** original) {
    void* handle = dlopen(library, RTLD_NOW);
    if (!handle) {
        handle = dlopen(nullptr, RTLD_NOW);
    }
    
    if (!handle) return false;
    
    *original = dlsym(handle, symbol);
    if (!*original) return false;
    
    // Simple hook implementation - replace with proper hooking mechanism
    *(void**)original = replacement;
    
    return true;
}

bool HookEngine::hookAllModules(const char* symbol, void* replacement, void** original) {
    std::ifstream proc_maps("/proc/self/maps");
    std::string line;
    
    while (std::getline(proc_maps, line)) {
        if (line.find(".so") != std::string::npos) {
            std::string lib_path = line.substr(0, line.find(' '));
            if (hookFunction(lib_path.c_str(), symbol, replacement, original)) {
                return true;
            }
        }
    }
    
    return false;
}

void* HookEngine::dlopen_ext(const char* filename, int flags) {
    return dlopen(filename, flags);
}

void* HookEngine::dlsym_ext(void* handle, const char* symbol) {
    return dlsym(handle, symbol);
}
=== END FILE ===
