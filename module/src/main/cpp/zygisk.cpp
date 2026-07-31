#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "RevenyZygisk"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {

void zygisk_init() {
    LOGD("Zygisk module initialized");
}

}
=== END FILE ===
