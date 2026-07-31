#include <jni.h>
#include <string>
#include <android/log.h>
#include "imgui/imgui.h"
#include "hook/HookEngine.h"
#include "hook/GraphicsHook.h"
#include "hook/TouchHook.h"

#define LOG_TAG "ImGuiMod"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void InitImGui();
void RenderImGui();
void CleanupImGui();

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_zygisk_imgui_MainActivity_initImGui(JNIEnv* env, jobject) {
    InitImGui();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_zygisk_imgui_MainActivity_renderImGui(JNIEnv* env, jobject) {
    RenderImGui();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_zygisk_imgui_MainActivity_cleanupImGui(JNIEnv* env, jobject) {
    CleanupImGui();
}

static void InitImGui() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    
    // Setup Platform/Renderer backends
    io.ImeWindowHandle = NULL;
    
    // Load font
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 16.0f;
    io.Fonts->AddFontDefault(&fontConfig);
}

static void RenderImGui() {
    static bool init = true;
    
    if (init) {
        HookEngine::Initialize();
        TouchHook::Initialize();
        init = false;
    }
    
    // Check if hook is active
    if (TouchHook::IsHookActive()) {
        // Draw ImGui menu
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(1920.0f, 1080.0f);
        
        ImGui::NewFrame();
        
        ImGui::Begin("Mod Menu", NULL, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("ImGui Mod Menu");
        ImGui::Checkbox("Enabled", &TouchHook::IsHookActive());
        ImGui::Button("Close");
        ImGui::End();
        
        ImGui::Render();
    }
}

static void CleanupImGui() {
    if (TouchHook::IsHookActive()) {
        TouchHook::DisableHook();
    }
    ImGui::DestroyContext();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reveny_zygisk_imgui_MainActivity_loadLibrary(JNIEnv* env, jobject, jstring libraryName) {
    const char* libName = env->GetStringUTFChars(libraryName, nullptr);
    std::string libPath = std::string(libName);
    LOGD("Loading library: %s", libName);
    env->ReleaseStringUTFChars(libraryName, libName);
}
