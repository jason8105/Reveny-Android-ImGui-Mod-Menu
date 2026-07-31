#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_reveny_modmenu_MainActivity_init(JNIEnv* env, jobject thiz) {
    void* handle = dlopen("libc.so", RTLD_NOW);
    if (handle) {
        dlclose(handle);
    }
}

}
=== END FILE ===
