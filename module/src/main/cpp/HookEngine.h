#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void PltHookAllModules();
    static void HookGraphicsFunction(const char* moduleName, const char* functionName, void* hookFunction);
    static void* GetModuleHandle(const char* moduleName);
    static void* GetFunctionAddress(const char* moduleName, const char* functionName);
};
=== END FILE ===
