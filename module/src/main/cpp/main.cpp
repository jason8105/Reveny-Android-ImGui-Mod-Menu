#define ZYGISK_API_IMPLEMENTATION
#include <zygisk.hpp>
#include <imgui/imgui.h>
#include <hook/HookEngine.h>
#include <hook/TouchHook.h>
#include <hook/GraphicsHook.h>

class RevenyModule : public zygisk::ModuleBase {
public:
    void onLoad(zygisk::Api* api, JNIEnv* env) override {
        api->setOption(zygisk::Option::PRE_INIT, nullptr);
        api->setOption(zygisk::Option::APP_DATA_DIR, nullptr);
        api->setOption(zygisk::Option::FORCE_DENYLIST_UNMOUNT, nullptr);
        
        // Initialize hooks for Android apps
        HookEngine::Initialize();
        TouchHook::Initialize();
        
        LOGD("Reveny Zygisk Module Loaded");
    }
    
    void preAppSpecialize(zygisk::SpecializeInfo* info) override {
        // Handle app specialization
        HookEngine::PreAppSpecialize(info);
    }
    
    void postAppSpecialize(const zygisk::SpecializeInfo* info) override {
        // Handle post specialization
        HookEngine::PostAppSpecialize(info);
    }
};

REGISTER_ZYGISK_MODULE(RevenyModule)
