#include <jni.h>
#include <dlfcn.h>
#include <string>
#include <thread>
#include <chrono>

extern "C" {
    void __attribute__((constructor)) zygisk_entry();
}

void __attribute__((constructor)) zygisk_entry() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    
    void* handle = dlopen("libandroid.so", RTLD_NOW);
    if (handle) {
        dlclose(handle);
    }
}
=== END FILE ===
