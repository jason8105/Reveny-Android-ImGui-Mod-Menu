#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <thread>
#include <chrono>

#define LOG_TAG "RevenyModMenu"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {
    void ZygiskInit(void* moduleHandle);
}

void ZygiskInit(void* moduleHandle) {
    LOGD("Zygisk module initialized");
    
    std::thread([]() {
        LOGD("Starting mod menu initialization");
        
        while (true) {
            void* handle = dlopen("libandroid_runtime.so", RTLD_NOW);
            if (handle) {
                LOGD("Found libandroid_runtime.so");
                dlclose(handle);
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        LOGD("Mod menu ready");
    }).detach();
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv* env, jobject /* this */) {
    LOGD("Mod menu initialized via JNI");
}
=== END FILE ===
