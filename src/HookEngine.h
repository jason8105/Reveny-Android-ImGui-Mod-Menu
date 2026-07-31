#pragma once

#include <string>
#include <vector>
#include <functional>

class HookEngine {
public:
    static void Initialize();
    static void Cleanup();
    static void PltHookAllModules();
    static void HookFunction(const char* moduleName, const char* functionName, void* replacement);
    static void* GetSymbol(const char* moduleName, const char* symbolName);
    static bool IsModuleLoaded(const char* moduleName);
    
private:
    static std::vector<std::string> g_loadedModules;
    static bool g_initialized;
};
=== END FILE ===
