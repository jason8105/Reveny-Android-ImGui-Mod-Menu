#include <jni.h>
#include <dlfcn.h>
#include <thread>
#include <cstring>
#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiHook.h"

void init_hooks() {
    HookEngine::PltHookAllModules();
    TouchHook::Initialize();
    ImGuiHook::Initialize();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initNative(JNIEnv *env, jobject /* this */) {
    std::thread(init_hooks).detach();
}
=== END FILE ===
