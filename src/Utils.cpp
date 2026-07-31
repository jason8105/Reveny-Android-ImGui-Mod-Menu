#include "Utils.h"
#include <android/log.h>

#define LOG_TAG "Utils"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool Utils::IsRooted() {
    char prop[PROP_VALUE_MAX];
    __system_property_get("ro.build.selinux", prop);
    return strcmp(prop, "1") != 0;
}

bool Utils::IsMagiskInstalled() {
    char prop[PROP_VALUE_MAX];
    __system_property_get("ro.magisk.version", prop);
    return strlen(prop) > 0;
}

int Utils::GetAndroidVersion() {
    char prop[PROP_VALUE_MAX];
    __system_property_get("ro.build.version.sdk", prop);
    return atoi(prop);
}

=== END FILE ===
