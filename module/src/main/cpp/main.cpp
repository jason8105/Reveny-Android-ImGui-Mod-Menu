#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>

#include "hook.h"
#include "touch_hook.h"
#include "imgui_impl.h"

static bool g_initialized = false;
static pthread_t g_hook_thread;

void init_hooks() {
    if (g_initialized) return;
    
    HookEngine::init();
    TouchHook::init();
    ImGuiImpl::init();
    
    g_initialized = true;
}

void deinit_hooks() {
    if (!g_initialized) return;
    
    ImGuiImpl::deinit();
    TouchHook::deinit();
    HookEngine::deinit();
    
    g_initialized = false;
}

void* hook_thread_func(void* arg) {
    init_hooks();
    
    while (true) {
        usleep(100000);
    }
    
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv* env, jobject /* this */) {
    if (!g_initialized) {
        pthread_create(&g_hook_thread, nullptr, hook_thread_func, nullptr);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_cleanupModMenu(JNIEnv* env, jobject /* this */) {
    deinit_hooks();
}
=== END FILE ===
