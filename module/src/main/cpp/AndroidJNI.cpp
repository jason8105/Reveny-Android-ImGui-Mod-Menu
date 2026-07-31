#include <jni.h>
#include <string>
#include "TouchHook.h"
#include "ImGuiRenderer.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_hookTouch(JNIEnv* env, jobject thiz) {
    TouchHook::SetMenuVisible(true);
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_unhookTouch(JNIEnv* env, jobject thiz) {
    TouchHook::SetMenuVisible(false);
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_setImGuiPos(JNIEnv* env, jobject thiz, jfloat x, jfloat y) {
    ImGuiRenderer::SetWindowPos(x, y);
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_setImGuiSize(JNIEnv* env, jobject thiz, jfloat width, jfloat height) {
    ImGuiRenderer::SetWindowSize(width, height);
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initImGui(JNIEnv* env, jobject thiz) {
    ImGuiRenderer::Initialize();
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_shutdownImGui(JNIEnv* env, jobject thiz) {
    ImGuiRenderer::Shutdown();
}

}
=== END FILE ===
