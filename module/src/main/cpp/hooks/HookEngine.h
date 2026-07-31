#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void Initialize();
    static void PltHookAllModules();
    static void HookFunction(const char* moduleName, const char* functionName, void* replacement);
};
=== END FILE ===
