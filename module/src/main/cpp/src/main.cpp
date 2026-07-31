#include <jni.h>
#include <dlfcn.h>
#include "HookEngine.h"
#include "TouchHook.h"
#include "GraphicsHook.h"

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    HookEngine::InitImGuiContext();
    HookEngine::PltHookAllModules();
    GraphicsHook::InitGraphicsHook();
    
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    HookEngine::ShutdownImGuiContext();
}

}

=== END FILE ===
