#pragma once

#include <dlfcn.h>
#include <string>
#include <vector>

class HookEngine {
public:
    static void* PltHookAllModules(const char* symbol, void* replacement, void** original);
    static void* PltHookModule(const char* module, const char* symbol, void* replacement, void** original);
    static void HookFunction(const char* symbol, void* replacement, void** original);
    static void HookFunction(const char* module, const char* symbol, void* replacement, void** original);
};

=== END FILE ===
