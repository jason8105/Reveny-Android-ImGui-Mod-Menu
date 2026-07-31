#include "HookEngine.h"
#include <dlfcn.h>
#include <cstring>
#include <vector>
#include <string>

namespace HookEngine {

void HookEngine::PltHookAllModules(const char* symbol, void* replacement, void** original) {
    Dl_info info;
    void* handle = dlopen(nullptr, RTLD_NOW | RTLD_LOCAL);
    
    if (handle) {
        Dl_info dl_info;
        if (dladdr(handle, &dl_info)) {
            // Get all loaded modules
            FILE* maps = fopen("/proc/self/maps", "r");
            if (maps) {
                char line[512];
                while (fgets(line, sizeof(line), maps)) {
                    if (strstr(line, ".so")) {
                        char* path = strchr(line, '/');
                        if (path) {
                            path[strcspn(path, "\n")] = 0;
                            void* so_handle = dlopen(path, RTLD_NOW);
                            if (so_handle) {
                                *original = dlsym(so_handle, symbol);
                                if (*original) {
                                    void* sym = dlsym(so_handle, symbol);
                                    if (sym) {
                                        // Hook logic here
                                    }
                                    dlclose(so_handle);
                                }
                            }
                        }
                    }
                }
                fclose(maps);
            }
        }
        dlclose(handle);
    }
}

void HookEngine::HookFunction(const char* module, const char* symbol, void* replacement, void** original) {
    void* handle = dlopen(module, RTLD_NOW);
    if (handle) {
        *original = dlsym(handle, symbol);
        // Apply hook
        dlclose(handle);
    }
}

} // namespace HookEngine
=== END FILE ===
