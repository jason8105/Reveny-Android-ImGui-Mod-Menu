#include "GraphicsHook.h"
#include "ImGuiRenderer.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <dlfcn.h>
#include <cstring>

namespace GraphicsHook {

static PFNEGLSWAPBUFFSEXTPROC originalEglSwapBuffers = nullptr;
static bool g_hooked = false;

void GraphicsHook::HookEglSwapBuffers() {
    if (g_hooked) return;
    
    void* egl_handle = dlopen("libEGL.so", RTLD_NOW);
    if (egl_handle) {
        originalEglSwapBuffers = (PFNEGLSWAPBUFFSEXTPROC)dlsym(egl_handle, "eglSwapBuffers");
        
        // Apply hook using your hooking mechanism
        // This would typically use frida, cydia-substrate, or similar
        g_hooked = true;
        dlclose(egl_handle);
    }
}

bool GraphicsHook::EglSwapBuffersHook(EGLDisplay display, EGLSurface surface) {
    // Render ImGui before swap
    ImGuiRenderer::Render();
    
    // Call original
    if (originalEglSwapBuffers) {
        return originalEglSwapBuffers(display, surface);
    }
    
    return false;
}

} // namespace GraphicsHook
=== END FILE ===
