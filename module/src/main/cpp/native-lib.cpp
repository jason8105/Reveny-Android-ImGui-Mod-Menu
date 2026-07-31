#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <pthread.h>

#define LOG_TAG "RevenyImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "HookEngine.h"
#include "TouchHook.h"

static bool g_initialized = false;
static bool g_menu_visible = false;

extern "C" {

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv* env, jobject thiz) {
    if (g_initialized) return;
    
    LOGD("Initializing Reveny Mod Menu");
    
    HookEngine::PltHookAllModules();
    TouchHook::Initialize();
    
    g_initialized = true;
    LOGD("Mod Menu initialized successfully");
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_setMenuVisible(JNIEnv* env, jobject thiz, jboolean visible) {
    g_menu_visible = visible;
    TouchHook::SetMenuVisible(visible);
}

JNIEXPORT jboolean JNICALL
Java_com_reveny_modmenu_MainActivity_isMenuVisible(JNIEnv* env, jobject thiz) {
    return g_menu_visible;
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_cleanup(JNIEnv* env, jobject thiz) {
    if (g_initialized) {
        TouchHook::Cleanup();
        g_initialized = false;
        g_menu_visible = false;
        LOGD("Mod Menu cleanup completed");
    }
}

}
=== END FILE ===
