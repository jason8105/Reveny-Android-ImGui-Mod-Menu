#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>

#include "hook_engine.h"
#include "imgui_renderer.h"
#include "touch_hook.h"

static bool g_initialized = false;
static pthread_t g_hook_thread;

extern "C" {

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv *env, jobject /* this */) {
    if (g_initialized) return;
    g_initialized = true;

    pthread_create(&g_hook_thread, nullptr, [] (void *arg) -> void * {
        HookEngine::init();
        TouchHook::init();
        ImGuiRenderer::init();
        return nullptr;
    }, nullptr);
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_cleanupModMenu(JNIEnv *env, jobject /* this */) {
    if (!g_initialized) return;
    g_initialized = false;

    ImGuiRenderer::cleanup();
    TouchHook::cleanup();
    HookEngine::cleanup();
}

}
=== END FILE ===
