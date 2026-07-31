#include <jni.h>
#include <string>
#include <android/log.h>
#include <dlfcn.h>
#include <pthread.h>

#define LOG_TAG "ZygiskImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace HookEngine {
    void PltHookAllModules();
    void InitImGuiContext();
    void RenderImGuiOverlay();
}

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad called");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnUnload called");
}

JNIEXPORT void JNICALL
Java_com_example_zygisk_imguitouch_MainActivity_initNative(JNIEnv* env, jobject thiz) {
    LOGD("initNative called");
    HookEngine::PltHookAllModules();
    HookEngine::InitImGuiContext();
}

JNIEXPORT void JNICALL
Java_com_example_zygisk_imguitouch_MainActivity_renderOverlay(JNIEnv* env, jobject thiz) {
    LOGD("renderOverlay called");
    HookEngine::RenderImGuiOverlay();
}

}
