#include <jni.h>
#include <string>
#include <vector>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#define LOG_TAG "RevenyImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace ImGui {

void SetNextWindowPos(float x, float y) {
    LOGD("SetNextWindowPos: %f, %f", x, y);
}

void SetNextWindowSize(float width, float height) {
    LOGD("SetNextWindowSize: %f, %f", width, height);
}

void Render() {
    LOGD("ImGui Render called");
}

}

extern "C" {

void eglSwapBuffers_hook(EGLDisplay display, EGLSurface surface) {
    ImGui::Render();
    LOGD("eglSwapBuffers hook executed");
}

}
=== END FILE ===
