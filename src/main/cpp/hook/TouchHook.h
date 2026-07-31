#pragma once

#include <android/input.h>
#include <android/looper.h>

class TouchHook {
public:
    static void Initialize();
    static void HookInputQueue();
    static void ProcessTouchEvent(AInputEvent* event);
    static bool IsTouchEnabled();
    static void SetTouchEnabled(bool enabled);
};

=== END FILE ===
