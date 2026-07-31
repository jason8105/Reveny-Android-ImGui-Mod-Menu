#include <jni.h>
#include <string>
#include <android/log.h>
#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"

#define LOG_TAG "RevenyImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_initNative(JNIEnv* env, jobject /* this */) {
    LOGD("Initializing native hooks...");
    
    HookEngine::Init();
    TouchHook::Init();
    ImGuiHook::Init();
    
    LOGD("Native hooks initialized successfully");
}

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_cleanupNative(JNIEnv* env, jobject /* this */) {
    LOGD("Cleaning up native hooks...");
    
    ImGuiHook::Cleanup();
    TouchHook::Cleanup();
    HookEngine::Cleanup();
    
    LOGD("Native hooks cleaned up");
}
=== END FILE ===
