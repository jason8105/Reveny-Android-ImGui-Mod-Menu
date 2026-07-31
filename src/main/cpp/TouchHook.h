#pragma once

#include <jni.h>

class TouchHook {
public:
    static void init();
    static void cleanup();
    
    static bool isMenuOpen();
    static void setMenuOpen(bool open);
    
private:
    static bool menuOpen;
    static void* originalAInputQueue_getEvent;
    static void* originalAInputQueue_getFd;
    
    static void* hookAInputQueue_getEvent(void* queue);
    static void* hookAInputQueue_getFd(void* queue);
};
