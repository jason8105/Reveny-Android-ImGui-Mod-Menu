#include <jni.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/system_properties.h>

extern "C" {
#include "dobby.h"
#include "KittyMemory/KittyMemory.h"
#include "KittyMemory/KittyUtils.h"
#include "KittyMemory/KittyProcess.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
}

#include "ImGui.h"
#include "TouchHook.h"
#include "HookEngine.h"
#include "Config.h"

bool IsZygisk() {
    char value[PROP_VALUE_MAX];
    __system_property_get("ro.zygisk", value);
    return strcmp(value, "true") == 0;
}

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_initHook(JNIEnv* env, jobject) {
    LOGI("Initializing Reveny ImGui Mod Menu");
    
    if (IsZygisk()) {
        LOGI("Running in Zygisk mode");
        HookEngine::Initialize();
        TouchHook::Initialize();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_drawOverlay(JNIEnv* env, jobject) {
    ImGui::NewFrame();
    
    if (ImGui::Begin("Reveny Mod Menu")) {
        if (ImGui::Button("Toggle Menu")) {
            HookEngine::ToggleMenu();
        }
        
        ImGui::SliderFloat("Speed", &Config::speed, 0.1f, 10.0f);
        ImGui::Checkbox("ESP", &Config::esp);
    }
    
    ImGui::End();
    ImGui::Render();
}

extern "C" JNIEXPORT void JNICALL
Java_com_reveny_main_MainActivity_hookOpenGL(JNIEnv* env, jobject) {
    HookEngine::HookOpenGL();
}
