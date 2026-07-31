#include "GraphicsHook.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_android.h"

#define LOG_TAG "GraphicsHook"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void GraphicsHook::Initialize() {
    LOGD("GraphicsHook initialized");
}

void GraphicsHook::HookEglSwapBuffers() {
    LOGD("Hooking eglSwapBuffers");
}
=== END FILE ===
