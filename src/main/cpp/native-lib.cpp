#include <jni.h>
#include <string>
#include <android/log.h>
#include <dlfcn.h>
#include <sys/system_properties.h>

#define LOG_TAG "ZygiskImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad called");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnUnload called");
}

JNIEXPORT void JNICALL Java_com_example_zygisk_imguitouch_MainActivity_initHooks(JNIEnv* env, jobject thiz) {
    LOGD("Initializing hooks...");
    
    HookEngine::init();
    TouchHook::init();
    ImGuiHook::init();
    
    LOGD("Hooks initialized successfully");
}

JNIEXPORT void JNICALL Java_com_example_zygisk_imguitouch_MainActivity_cleanupHooks(JNIEnv* env, jobject thiz) {
    LOGD("Cleaning up hooks...");
    
    ImGuiHook::cleanup();
    TouchHook::cleanup();
    HookEngine::cleanup();
    
    LOGD("Hooks cleaned up");
}

}
