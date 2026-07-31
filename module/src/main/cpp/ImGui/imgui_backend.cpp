#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <sys/system_properties.h>
#include <android/log.h>

#define LOG_TAG "ImGuiBackend"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static EGLDisplay g_eglDisplay = EGL_NO_DISPLAY;
static EGLSurface g_eglSurface = EGL_NO_SURFACE;
static EGLContext g_eglContext = EGL_NO_CONTEXT;
static ANativeWindow* g_nativeWindow = nullptr;

bool ImGuiBackend_Init(ANativeWindow* window) {
    g_nativeWindow = window;
    
    g_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_eglDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay failed");
        return false;
    }
    
    EGLint major, minor;
    if (!eglInitialize(g_eglDisplay, &major, &minor)) {
        LOGE("eglInitialize failed");
        return false;
    }
    
    EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    
    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(g_eglDisplay, configAttribs, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig failed");
        return false;
    }
    
    g_eglSurface = eglCreateWindowSurface(g_eglDisplay, config, g_nativeWindow, nullptr);
    if (g_eglSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface failed");
        return false;
    }
    
    EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };
    
    g_eglContext = eglCreateContext(g_eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);
    if (g_eglContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext failed");
        return false;
    }
    
    if (!eglMakeCurrent(g_eglDisplay, g_eglSurface, g_eglSurface, g_eglContext)) {
        LOGE("eglMakeCurrent failed");
        return false;
    }
    
    ImGui_ImplAndroid_Init(window);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    LOGD("ImGui backend initialized");
    return true;
}

void ImGuiBackend_Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    
    if (g_eglContext != EGL_NO_CONTEXT) {
        eglDestroyContext(g_eglDisplay, g_eglContext);
        g_eglContext = EGL_NO_CONTEXT;
    }
    
    if (g_eglSurface != EGL_NO_SURFACE) {
        eglDestroySurface(g_eglDisplay, g_eglSurface);
        g_eglSurface = EGL_NO_SURFACE;
    }
    
    if (g_eglDisplay != EGL_NO_DISPLAY) {
        eglTerminate(g_eglDisplay);
        g_eglDisplay = EGL_NO_DISPLAY;
    }
    
    g_nativeWindow = nullptr;
    LOGD("ImGui backend shutdown");
}

void ImGuiBackend_Render() {
    if (g_eglDisplay == EGL_NO_DISPLAY) return;
    
    eglSwapBuffers(g_eglDisplay, g_eglSurface);
}
=== END FILE ===
