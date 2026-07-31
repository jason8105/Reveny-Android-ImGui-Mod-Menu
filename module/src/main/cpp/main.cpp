#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <thread>
#include <chrono>

#define LOG_TAG "RevenyModMenu"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"

static bool g_initialized = false;

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv* env, jobject thiz) {
    if (g_initialized) return;
    g_initialized = true;

    LOGD("Initializing Reveny Mod Menu");

    std::thread initThread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        HookEngine::init();
        HookEngine::PltHookAllModules();

        TouchHook::init();
        ImGuiHook::init();

        LOGD("Mod Menu initialized successfully");
    });

    initThread.detach();
}

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_cleanupModMenu(JNIEnv* env, jobject thiz) {
    if (!g_initialized) return;
    g_initialized = false;

    LOGD("Cleaning up Reveny Mod Menu");

    ImGuiHook::cleanup();
    TouchHook::cleanup();
    HookEngine::cleanup();
}
=== END FILE ===
