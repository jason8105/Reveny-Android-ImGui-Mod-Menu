#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <thread>
#include <chrono>

extern "C" {
    void ZygiskInit();
    void HookEngine::PltHookAllModules();
    void TouchHook::Initialize();
    void ImGuiRenderer::Render();
}

void ZygiskInit() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    HookEngine::PltHookAllModules();
    TouchHook::Initialize();
    
    std::thread renderThread([]() {
        while (true) {
            ImGuiRenderer::Render();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    });
    renderThread.detach();
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initMod(JNIEnv *env, jobject /* this */) {
    ZygiskInit();
}
=== END FILE ===
