#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void init();
    static void cleanup();
    static void hookFunction(const char* moduleName, const char* functionName, void* replacement);
    static void hookAllModules(const char* functionName, void* replacement);
};
=== END FILE ===
