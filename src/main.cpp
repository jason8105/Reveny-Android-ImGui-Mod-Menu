#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <thread>
#include <atomic>

#define LOG_TAG "ZygiskImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"
#include "TouchInjection.h"

static std::atomic<bool> g_initialized{false};
static std::atomic<bool> g_menuVisible{false};

extern "C" {

JNIEXPORT void JNICALL
Java_com_zygisk_imgui_touchfix_MainActivity_initZygisk(JNIEnv* env, jobject thiz) {
    if (g_initialized.load()) return;
    
    LOGD("Initializing Zygisk ImGui Touch Fix module");
    
    HookEngine::Initialize();
    TouchHook::Initialize();
    ImGuiHook::Initialize();
    
    g_initialized.store(true);
    LOGD("Zygisk ImGui Touch Fix initialized successfully");
}

JNIEXPORT void JNICALL
Java_com_zygisk imgui_touchfix_MainActivity_toggleMenu(JNIEnv* env, jobject thiz) {
    g_menuVisible.store(!g_menuVisible.load());
    LOGD("Menu toggle: %s", g_menuVisible.load() ? "OPEN" : "CLOSED");
}

JNIEXPORT jboolean JNICALL
Java_com_zygisk_imgui_touchfix_MainActivity_isMenuVisible(JNIEnv* env, jobject thiz) {
    return g_menuVisible.load();
}

JNIEXPORT void JNICALL
Java_com_zygisk_imgui_touchfix_MainActivity_setTouchEnabled(JNIEnv* env, jobject thiz, jboolean enabled) {
    TouchHook::SetEnabled(enabled);
    LOGD("Touch hook enabled: %s", enabled ? "true" : "false");
}

JNIEXPORT void JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad called");
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnUnload called");
    HookEngine::Cleanup();
    TouchHook::Cleanup();
    ImGuiHook::Cleanup();
}

}
=== END FILE ===
