#include <jni.h>
#include <string>
#include <android/log.h>
#include "hooks/HookEngine.h"
#include "hooks/TouchHook.h"
#include "hooks/GraphicsHook.h"

#define LOG_TAG "RevenyImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_initNative(JNIEnv *env, jobject /* this */) {
    LOGD("Native library initialized");
    
    HookEngine::Initialize();
    TouchHook::Initialize();
    GraphicsHook::Initialize();
    
    HookEngine::PltHookAllModules();
}
=== END FILE ===
