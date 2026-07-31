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
    void ZygiskInit();
    void ZygiskPreAppSpecialize(struct android_app* app);
    void ZygiskPostAppSpecialize(const char* /*data*/);
}

void* g_eglSwapBuffers = nullptr;
void* g_eglSwapInterval = nullptr;

void hookEGL() {
    void* libEGL = dlopen("libEGL.so", RTLD_NOW);
    if (!libEGL) {
        LOGE("Failed to load libEGL.so");
        return;
    }

    g_eglSwapBuffers = dlsym(libEGL, "eglSwapBuffers");
    g_eglSwapInterval = dlsym(libEGL, "eglSwapInterval");
    LOGD("EGL hooks initialized");
}

void renderImGui() {
    static bool initialized = false;
    if (!initialized) {
        hookEGL();
        initialized = true;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_initModMenu(JNIEnv* env, jobject /*this*/) {
    LOGD("ModMenu initialized");
    std::thread([]() {
        while (true) {
            renderImGui();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }).detach();
}
=== END FILE ===
