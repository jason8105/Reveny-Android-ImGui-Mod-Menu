#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include "HookEngine.h"
#include "ImGuiHook.h"
#include "TouchHook.h"

#define LOG_TAG "RevenyMod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Reveny Mod JNI_OnLoad called");
    
    ImGuiHook::InitImGui();
    
    void* original = nullptr;
    if (HookEngine::PltHookAllModules("eglSwapBuffers", nullptr, &original)) {
        LOGI("eglSwapBuffers hook found");
    }
    
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGI("Reveny Mod JNI_OnUnload called");
    ImGuiHook::CleanupImGui();
}

}
=== END FILE ===
