#include <jni.h>
#include "HookEngine.h"
#include "TouchHook.h"
#include "ImGuiRenderer.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initNative(JNIEnv* env, jobject /* this */) {
    HookEngine::PltHookAllModules();
    HookEngine::HookEGLSwapBuffers();
    TouchHook::InitTouchHook();
    ImGuiRenderer::Init();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_renderOverlay(JNIEnv* env, jobject /* this */) {
    ImGuiRenderer::Render();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_cleanupNative(JNIEnv* env, jobject /* this */) {
    ImGuiRenderer::Shutdown();
}
=== END FILE ===
