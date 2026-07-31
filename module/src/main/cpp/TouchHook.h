#ifndef TOUCH_HOOK_H
#define TOUCH_HOOK_H

namespace TouchHook {
    void Init();
    bool IsMenuOpen();
    void InjectTouch(int x, int y, int action);
}

#endif
=== END FILE ===
