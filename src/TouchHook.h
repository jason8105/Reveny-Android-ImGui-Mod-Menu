#pragma once

#include <atomic>

class TouchHook {
public:
    static void Initialize();
    static void Cleanup();
    static void SetEnabled(bool enabled);
    static bool IsEnabled();
    static void InjectTouch(int x, int y, int action, int pointerId = 0);
    static void ProcessTouchEvent(int x, int y, int action, int pointerId = 0);
    
private:
    static std::atomic<bool> g_enabled;
    static bool g_touchIntercepted;
    static void* g_originalAInputQueue_getEvent;
    static void* g_originalAInputQueue_getEventImpl(void* queue, void* event);
};
=== END FILE ===
