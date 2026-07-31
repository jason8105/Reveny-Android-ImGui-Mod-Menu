#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void Init();
    static void Cleanup();
    static void HookAllModules();
    
private:
    static bool initialized;
};
=== END FILE ===
