#include <jni.h>
#include <android/input.h>
#include <android/looper.h>
#include <android/queue.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>

#define LOG_TAG "TouchHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace TouchHook {

static void* g_input_queue = nullptr;
static bool g_menu_open = false;

void HookInputQueue() {
    LOGD("HookInputQueue called");
}

bool IsMenuOpen() {
    return g_menu_open;
}

void SetMenuOpen(bool open) {
    g_menu_open = open;
}

int InterceptTouchEvent(void* event) {
    if (g_menu_open) {
        LOGD("Touch event intercepted by menu");
        return 1;
    }
    return 0;
}

}
