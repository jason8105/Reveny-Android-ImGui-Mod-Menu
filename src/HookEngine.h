#pragma once

#include <jni.h>

class HookEngine {
public:
    static void Initialize();
    static void Shutdown();
    static void SetJavaVM(JavaVM* vm);
    static JavaVM* GetJavaVM();
    static void PltHookAllModules();

private:
    static JavaVM* g_javaVM;
    static bool g_initialized;
};

=== END FILE ===
