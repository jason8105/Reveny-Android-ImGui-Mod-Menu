#include "HookEngine.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "HookEngine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace HookEngine {
    void PltHookAllModules() {
        LOGD("Hooking all modules");
    }

    void InitImGui() {
        LOGD("ImGui initialized");
    }
}
=== END FILE ===
