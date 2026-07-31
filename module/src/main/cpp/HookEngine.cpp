#include "HookEngine.h"
#include <dlfcn.h>
#include <cstring>

namespace HookEngine {

void PltHookAllModules() {
    void* handle = dlopen(nullptr, RTLD_NOW | RTLD_GLOBAL);
    if (handle) {
        dlclose(handle);
    }
}

}
=== END FILE ===
