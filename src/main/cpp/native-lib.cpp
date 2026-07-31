#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include "hook/HookEngine.h"
#include "hook/TouchHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_android.h"
#include "imgui/imgui_impl_opengl3.h"

#define LOG_TAG "ZygiskImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static bool g_initialized = false;
static bool g_menuVisible = true;
static bool g_touchEnabled = true;

extern "C" {

void initImGuiContext() {
    if (g_initialized) return;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplAndroid_Init(nullptr);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    g_initialized = true;
    LOGD("ImGui context initialized");
}

void renderImGui() {
    if (!g_initialized) return;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    
    if (g_menuVisible) {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(300, 500));
        
        ImGui::Begin("Game Mod Menu", &g_menuVisible, ImGuiWindowFlags_NoCollapse);
        
        ImGui::Text("Zygisk ImGui Module");
        ImGui::Separator();
        
        ImGui::Checkbox("Menu Visible", &g_menuVisible);
        ImGui::Checkbox("Touch Enabled", &g_touchEnabled);
        
        if (ImGui::Button("Inject")) {
            LOGD("Inject button pressed");
        }
        
        ImGui::End();
    }
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void* graphicsThread(void* arg) {
    while (true) {
        renderImGui();
        usleep(16000);
    }
    return nullptr;
}

void hookGraphics() {
    void* libEGL = dlopen("libEGL.so", RTLD_NOW);
    void* libGLESv2 = dlopen("libGLESv2.so", RTLD_NOW);
    
    if (!libEGL || !libGLESv2) {
        LOGD("Failed to load graphics libraries");
        return;
    }
    
    HookEngine::PltHookAllModules("eglSwapBuffers", 
        reinterpret_cast<void*>(eglSwapBuffers),
        reinterpret_cast<void*>(eglSwapBuffers_Original));
    
    LOGD("Graphics hooks installed");
}

void hookTouch() {
    TouchHook::Initialize();
    LOGD("Touch hooks installed");
}

void* zygiskInit(void* args) {
    LOGD("Zygisk module initialized");
    
    initImGuiContext();
    hookGraphics();
    hookTouch();
    
    pthread_t thread;
    pthread_create(&thread, nullptr, graphicsThread, nullptr);
    
    return nullptr;
}

__attribute__((constructor))
void moduleInit() {
    LOGD("Native library loaded");
}

}

=== END FILE ===
