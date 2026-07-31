#include "HookEngine.h"
#include <dlfcn.h>
#include <cstring>

void HookEngine::PltHookAllModules() {
    void* handle = dlopen("libandroid.so", RTLD_NOW);
    if (handle) {
        dlclose(handle);
    }
}
=== END FILE ===
