#include <jni.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"
#include "Utils.h"

#define LOG_TAG "ImGuiHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static bool g_initialized = false;
static bool g_menuVisible = false;
static bool g_touchEnabled = true;

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_mod_MainActivity_initHook(JNIEnv* env, jobject thiz) {
    if (g_initialized) return;
    
    LOGD("Initializing Zygisk ImGui Hook Module");
    
    HookEngine::Initialize();
    TouchHook::Initialize();
    ImGuiHook::Initialize();
    
    g_initialized = true;
    LOGD("Hook initialization complete");
}

JNIEXPORT void JNICALL
Java_com_example_mod_MainActivity_toggleMenu(JNIEnv* env, jobject thiz) {
    g_menuVisible = !g_menuVisible;
    LOGD("Menu visibility toggled: %s", g_menuVisible ? "ON" : "OFF");
}

JNIEXPORT void JNICALL
Java_com_example_mod_MainActivity_setTouchEnabled(JNIEnv* env, jobject thiz, jboolean enabled) {
    g_touchEnabled = enabled;
    LOGD("Touch enabled: %s", enabled ? "ON" : "OFF");
}

JNIEXPORT jboolean JNICALL
Java_com_example_mod_MainActivity_isMenuVisible(JNIEnv* env, jobject thiz) {
    return g_menuVisible;
}

JNIEXPORT void JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad called");
    
    JNIEnv* env;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("Failed to get JNI environment");
        return;
    }
    
    HookEngine::SetJavaVM(vm);
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnUnload called");
    
    if (g_initialized) {
        ImGuiHook::Shutdown();
        TouchHook::Shutdown();
        HookEngine::Shutdown();
        g_initialized = false;
    }
}

} // extern "C"

=== END FILE ===
