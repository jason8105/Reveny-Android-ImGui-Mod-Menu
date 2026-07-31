#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>

extern "C" {
    void hook_init();
    void hook_cleanup();
}

static void* thread_func(void* arg) {
    sleep(3);
    hook_init();
    return nullptr;
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_init(JNIEnv* env, jobject thiz) {
    pthread_t thread;
    pthread_create(&thread, nullptr, thread_func, nullptr);
}
}
=== END FILE ===
