#include <jni.h>
#include <string>
#include <dlfcn.h>
#include "hooks/HookEngine.h"
#include "hooks/TouchHook.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initNative(JNIEnv *env, jobject /* this */) {
    HookEngine::init();
    TouchHook::init();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_reveny_modmenu_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Reveny ImGui Mod Menu";
    return env->NewStringUTF(hello.c_str());
}
=== END FILE ===
