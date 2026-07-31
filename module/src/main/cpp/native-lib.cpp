#define __STDC_LIMIT_MACROS
#include <dlfcn.h>
#include <jni.h>
#include <android/log.h>
#include <cstring>
#include <vector>
#include <functional>
#include <mutex>
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "KittyMemory/KittyMemory.h"
#include "KittyMemory/KittyUtils.h"

#define LOG_TAG "RevenyModMenu"
#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace HookEngine {
    static void* eglSwapBuffersHandle = nullptr;

    void InitHooks() {
        LOG("Initializing hooks...");
        void* eglModule = dlopen("libEGL.so", RTLD_NOW);
        if (eglModule) {
            LOG("Found libEGL.so");
        }
    }
}

static jobject gActivity = nullptr;
static jobject gEGLSurface = nullptr;
static bool gMenuVisible = false;
static std::mutex gMenuMutex;

extern "C" JNIEXPORT void JNICALL
Java_com_modmenu_MainActivity_init(JNIEnv* env, jobject thiz) {
    LOG("ModMenu initialized");
    gActivity = env->NewGlobalRef(thiz);
    HookEngine::InitHooks();
}

void RenderMenu() {
    if (!gMenuVisible) return;

    ImGui::Begin("Reveny Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Toggle Menu")) {
        gMenuVisible = false;
        ImGui_ImplAndroid_InvalidateDeviceObjects();
    }

    ImGui::Text("Reveny Android ImGui Mod Menu");
    ImGui::Separator();
    ImGui::End();
}

void ProcessTouch(float x, float y) {
    ImGui_ImplAndroid_ProcessTouch(x, y);
}

extern "C" JNIEXPORT void JNICALL
Java_com_modmenu_MainActivity_onTouch(JNIEnv* env, jobject thiz, jfloat x, jfloat y) {
    ProcessTouch(x, y);
    RenderMenu();
}
