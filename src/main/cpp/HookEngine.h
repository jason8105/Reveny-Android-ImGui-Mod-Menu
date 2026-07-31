#pragma once

#include <string>
#include <vector>
#include <functional>

class HookEngine {
public:
    static void init();
    static void cleanup();
    
    static bool PltHookAllModules(const std::string& moduleName, const std::string& functionName, void* hookFunction, void** originalFunction);
    static bool PltHookFunction(const std::string& moduleName, const std::string& functionName, void* hookFunction, void** originalFunction);
    
    static void* dlsymHandle(const std::string& symbol);
    static void* dlopenHandle(const std::string& path, int flags);
    
private:
    static bool initialized;
    static std::vector<void*> loadedHandles;
};
