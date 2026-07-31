#pragma once

#include <string>
#include <vector>

class HookEngine {
public:
    static void init();
    static void PltHookAllModules();
    static void cleanup();

private:
    static bool g_initialized;
};
=== END FILE ===
