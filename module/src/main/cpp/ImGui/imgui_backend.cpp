#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>

#define LOG_TAG "RevenyImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static EGLDisplay g_display = EGL_NO_DISPLAY;
static EGLSurface g_surface = EGL_NO_SURFACE;
static EGLContext g_context = EGL_NO_CONTEXT;

void ImGuiBackend_Init() {
    LOGD("ImGuiBackend initialized");
    
    g_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_display == EGL_NO_DISPLAY) {
        LOGD("eglGetDisplay failed");
        return;
    }
    
    EGLint major, minor;
    eglInitialize(g_display, &major, &minor);
    
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
    eglChooseConfig(g_display, configAttribs, &config, 1, &numConfigs);
    
    g_surface = eglCreateWindowSurface(g_display, config, nullptr, nullptr);
    g_context = eglCreateContext(g_display, config, nullptr, nullptr);
    
    eglMakeCurrent(g_display, g_surface, g_surface, g_context);
    
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
}

void ImGuiBackend_Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    
    ImGui::ShowDemoWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    eglSwapBuffers(g_display, g_surface);
}

void ImGuiBackend_Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    
    if (g_context != EGL_NO_CONTEXT) {
        eglDestroyContext(g_display, g_context);
    }
    if (g_surface != EGL_NO_SURFACE) {
        eglDestroySurface(g_display, g_surface);
    }
    if (g_display != EGL_NO_DISPLAY) {
        eglTerminate(g_display);
    }
}
=== END FILE ===
