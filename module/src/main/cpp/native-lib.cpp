#include <jni.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <sys/system_properties.h>
#include <dlfcn.h>

#include "HookEngine/HookEngine.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/imgui_impl_opengles2.h"
#include "KittyMemory/KittyMemory.h"
#include "touch/TouchHook.h"

#define LOG_TAG "RevenyModMenu"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static bool gInitialized = false;
static TouchHook* gTouchHook = nullptr;
static bool gMenuVisible = false;

extern "C" {

JNIEXPORT void JNICALL Java_com_reveny_modmenu_MainActivity_init(JNIEnv* env, jobject thiz) {
    if (gInitialized) return;
    
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Initializing Reveny Mod Menu");
    
    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Initialize ImGui backends
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    // Initialize touch hook
    gTouchHook = new TouchHook();
    gTouchHook->Enable();
    
    gInitialized = true;
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Mod Menu Initialized");
}

JNIEXPORT void JNICALL Java_com_reveny_modmenu_MainActivity_cleanup(JNIEnv* env, jobject thiz) {
    if (!gInitialized) return;
    
    if (gTouchHook) {
        gTouchHook->Disable();
        delete gTouchHook;
        gTouchHook = nullptr;
    }
    
    ImGui::DestroyContext();
    gInitialized = false;
}

JNIEXPORT void JNICALL Java_com_reveny_modmenu_MainActivity_setMenuVisible(JNIEnv* env, jobject thiz, jboolean visible) {
    gMenuVisible = visible;
    if (gTouchHook) {
        gTouchHook->setMenuVisible(visible);
    }
}

JNIEXPORT jboolean JNICALL Java_com_reveny_modmenu_MainActivity_isMenuVisible(JNIEnv* env, jobject thiz) {
    return gMenuVisible;
}

JNIEXPORT void JNICALL Java_com_reveny_modmenu_MainActivity_hookGraphics(JNIEnv* env, jobject thiz) {
    HookEngine::PltHookAllModules("libOpenCL.so", 
        "eglSwapBuffers", 
        (void*)eglSwapBuffers_hook, 
        (void**)&original_eglSwapBuffers);
}

}

// EGL SwapBuffers hook for ImGui rendering
typedef EGLBoolean (*original_eglSwapBuffers_t)(EGLDisplay, EGLSurface);
original_eglSwapBuffers_t original_eglSwapBuffers;

EGLBoolean eglSwapBuffers_hook(EGLDisplay display, EGLSurface surface) {
    if (gMenuVisible) {
        ImGui_ImplAndroid_NewFrame();
        ImGui_ImplOpenGLES_NewFrame();
        ImGui::NewFrame();
        
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 400));
        
        ImGui::Begin("Reveny Mod Menu");
        
        ImGui::Text("Mod Menu Active");
        ImGui::Separator();
        
        if (ImGui::Button("Toggle Menu")) {
            gMenuVisible = !gMenuVisible;
            if (gTouchHook) {
                gTouchHook->setMenuVisible(gMenuVisible);
            }
        }
        
        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGLES_RenderDrawData(ImGui::GetDrawData());
    }
    
    return original_eglSwapBuffers(display, surface);
}
