#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>

extern "C" {
    void hook_init();
    void render_loop();
    void touch_hook_init();
}

static void* zygosk_thread(void* arg) {
    sleep(2);
    hook_init();
    touch_hook_init();
    render_loop();
    return nullptr;
}

JNIEXPORT void JNICALL
Java_com_reveny_modmenu_MainActivity_nativeInit(JNIEnv* env, jobject /* this */) {
    pthread_t thread;
    pthread_create(&thread, nullptr, zygosk_thread, nullptr);
}

}

=== END FILE ===
