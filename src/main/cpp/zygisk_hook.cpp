#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "ZygiskHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {

void zygisk_entry() {
    LOGD("Zygisk entry point called");
    
    HookEngine::PltHookAllModules();
    HookEngine::InitImGuiContext();
    TouchHook::HookInputQueue();
}

}
