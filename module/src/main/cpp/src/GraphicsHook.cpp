#include "GraphicsHook.h"
#include "HookEngine.h"
#include "TouchHook.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <jni.h>

namespace GraphicsHook {

static PFNEGLSWAPBUFFERSPROC g_eglSwapBuffers = nullptr;
static PFNEGLSWAPBUFFERSPROC g_originalSwapBuffers = nullptr;

void InitGraphicsHook() {
    void* egl = dlopen("libEGL.so", RTLD_NOW);
    if (egl) {
        g_eglSwapBuffers = (PFNEGLSWAPBUFFERSPROC)dlsym(egl, "eglSwapBuffers");
    }
}

void HookEglSwapBuffers() {
    if (g_eglSwapBuffers) {
        g_originalSwapBuffers = g_eglSwapBuffers;
    }
}

void RenderImGui() {
    ImGui::NewFrame();
    
    if (ImGui::Begin("Reveny Menu")) {
        ImGui::Text("Reveny ImGui Mod Menu");
        ImGui::Separator();
        
        static bool showDemo = false;
        if (ImGui::Checkbox("Show Demo", &showDemo)) {
            TouchHook::SetMenuVisible(showDemo);
        }
        
        if (showDemo) {
            ImGui::ShowDemoWindow();
        }
    }
    ImGui::End();
    
    ImGui::Render();
}

void OnSwapBuffers(EGLDisplay display, EGLSurface surface) {
    if (g_originalSwapBuffers) {
        g_originalSwapBuffers(display, surface);
    }
    
    RenderImGui();
}

} // namespace GraphicsHook

=== END FILE ===
