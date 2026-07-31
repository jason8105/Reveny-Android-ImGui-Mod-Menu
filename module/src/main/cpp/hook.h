#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void init();
    static void deinit();
    
    static bool hookFunction(const char* library, const char* symbol, void* replacement, void** original);
    static bool hookAllModules(const char* symbol, void* replacement, void** original);
    
    static void* dlopen_ext(const char* filename, int flags);
    static void* dlsym_ext(void* handle, const char* symbol);
    
private:
    static std::vector<std::string> g_loaded_libraries;
};
=== END FILE ===
