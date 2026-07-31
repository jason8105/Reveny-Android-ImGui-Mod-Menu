#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/system_properties.h>

#define LOG_TAG "ZygiskImGui"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, LOG_TAG, __VA_ARGS__)

#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"

namespace HookEngine {
    class PltHook {
    public:
        static void HookAllModules() {
            LOGD("HookEngine: Hooking all modules");
        }
    };
}

namespace TouchHook {
    class TouchInterceptor {
    private:
        bool menuVisible = false;
        AInputQueue* inputQueue = nullptr;
        ALooper* looper = nullptr;
        int32_t eventSource = 0;
        int32_t action = 0;
        float x = 0.0f;
        float y = 0.0f;

    public:
        void Initialize() {
            LOGD("TouchInterceptor: Initialized");
        }

        bool IsMenuVisible() const {
            return menuVisible;
        }

        void SetMenuVisible(bool visible) {
            menuVisible = visible;
        }

        void ProcessTouchEvent(int32_t source, int32_t action, float x, float y) {
            this->eventSource = source;
            this->action = action;
            this->x = x;
            this->y = y;

            if (menuVisible) {
                ImGuiIO& io = ImGui::GetIO();
                if (action == AKEY_EVENT_ACTION_DOWN || action == AKEY_EVENT_ACTION_UP) {
                    io.AddMouseButtonEvent(0, action == AKEY_EVENT_ACTION_DOWN);
                    io.AddMousePosEvent(x, y);
                }
            }
        }
    };

    TouchInterceptor interceptor;
}

namespace ImGuiHook {
    class ImGuiRenderer {
    private:
        ImGuiContext* imguiContext = nullptr;
        EGLDisplay eglDisplay = EGL_NO_DISPLAY;
        EGLSurface eglSurface = EGL_NO_SURFACE;
        EGLContext eglContext = EGL_NO_CONTEXT;
        bool initialized = false;

    public:
        void Initialize() {
            if (initialized) return;

            imguiContext = ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui::StyleColorsDark();

            initialized = true;
            LOGD("ImGuiRenderer: Initialized");
        }

        void Render() {
            if (!initialized) return;

            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(100, 100));
            ImGui::SetNextWindowSize(ImVec2(300, 400));

            ImGui::Begin("Game Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);

            static bool showDemo = false;
            ImGui::Checkbox("Show Demo", &showDemo);

            static bool toggleMenu = false;
            ImGui::Checkbox("Toggle Menu", &toggleMenu);

            static float speed = 1.0f;
            ImGui::SliderFloat("Speed", &speed, 0.1f, 5.0f);

            ImGui::End();

            if (showDemo) {
                ImGui::ShowDemoWindow();
            }

            ImGui::Render();
        }

        void Shutdown() {
            if (imguiContext) {
                ImGui::DestroyContext(imguiContext);
                imguiContext = nullptr;
            }
            initialized = false;
        }
    };

    ImGuiRenderer renderer;
}

static void* eglSwapBuffersHook(void* display, void* surface) {
    ImGuiHook::renderer.Render();
    return eglSwapBuffers((EGLDisplay)display, (EGLSurface)surface);
}

static void* eglSwapIntervalHook(void* display, int interval) {
    return eglSwapInterval((EGLDisplay)display, interval);
}

static void* AInputQueue_getEventHook(void* queue, void* event) {
    TouchHook::interceptor.ProcessTouchEvent(0, 0, 0, 0);
    return AInputQueue_getEvent((AInputQueue*)queue, (AInputEvent*)event);
}

static void* AInputQueue_preDispatchEventHook(void* queue, void* event, int32_t result) {
    TouchHook::interceptor.ProcessTouchEvent(0, 0, 0, 0);
    return AInputQueue_preDispatchEvent((AInputQueue*)queue, (AInputEvent*)event, result);
}

static void* AInputQueue_detachWindowHook(void* queue) {
    return AInputQueue_detachWindow((AInputQueue*)queue);
}

static void* AInputQueue_attachWindowHook(void* queue, void* window) {
    return AInputQueue_attachWindow((AInputQueue*)queue, (ANativeWindow*)window);
}

static void* AInputQueue_getFdHook(void* queue) {
    return AInputQueue_getFd((AInputQueue*)queue);
}

static void* AInputQueue_setEventThreadLooperHook(void* queue, void* looper) {
    return AInputQueue_setEventThreadLooper((AInputQueue*)queue, (ALooper*)looper);
}

static void* AInputQueue_getDisplayHeightHook(void* queue) {
    return AInputQueue_getDisplayHeight((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayWidthHook(void* queue) {
    return AInputQueue_getDisplayWidth((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayRotationHook(void* queue) {
    return AInputQueue_getDisplayRotation((AInputQueue*)queue);
}

static void* AInputQueue_getDisplaySizeHook(void* queue, void* width, void* height) {
    return AInputQueue_getDisplaySize((AInputQueue*)queue, (int*)width, (int*)height);
}

static void* AInputQueue_getDisplayDensityHook(void* queue) {
    return AInputQueue_getDisplayDensity((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayOrientationHook(void* queue) {
    return AInputQueue_getDisplayOrientation((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayScaleHook(void* queue) {
    return AInputQueue_getDisplayScale((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayDpiHook(void* queue) {
    return AInputQueue_getDisplayDpi((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayPixelRatioHook(void* queue) {
    return AInputQueue_getDisplayPixelRatio((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayRefreshRateHook(void* queue) {
    return AInputQueue_getDisplayRefreshRate((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorSpaceHook(void* queue) {
    return AInputQueue_getDisplayColorSpace((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayHdrCapabilitiesHook(void* queue) {
    return AInputQueue_getDisplayHdrCapabilities((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorGamutHook(void* queue) {
    return AInputQueue_getDisplayColorGamut((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorDepthHook(void* queue) {
    return AInputQueue_getDisplayColorDepth((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorModeHook(void* queue) {
    return AInputQueue_getDisplayColorMode((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorProfileHook(void* queue) {
    return AInputQueue_getDisplayColorProfile((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHook(void* queue) {
    return AInputQueue_getDisplayColorTemperature((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureRangeHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureRange((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureStepHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureStep((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureDefaultHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureDefault((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureMinHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureMin((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureMaxHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureMax((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureCurrentHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureCurrent((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureTargetHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureTarget((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureHistory((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistorySizeHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureHistorySize((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryIndexHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureHistoryIndex((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueHook(void* queue, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryValue((AInputQueue*)queue, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampHook(void* queue, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestamp((AInputQueue*)queue, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtHook(void* queue, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAt((AInputQueue*)queue, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtHook(void* queue, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAt((AInputQueue*)queue, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueRangeHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueRange((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampRangeHook(void* queue) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampRange((AInputQueue*)queue);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeHook(void* queue, int start, int end) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRange((AInputQueue*)queue, start, end);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeHook(void* queue, int start, int end) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRange((AInputQueue*)queue, start, end);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeSizeHook(void* queue, int start, int end) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeSize((AInputQueue*)queue, start, end);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeSizeHook(void* queue, int start, int end) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeSize((AInputQueue*)queue, start, end);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeIndexHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeIndex((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeIndexHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeIndex((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeValueHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeValue((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeValueHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeValue((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeTimestampHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeTimestamp((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeTimestampHook(void* queue, int start, int end, int index) {
    return AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeTimestamp((AInputQueue*)queue, start, end, index);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeValueAtHook(void* queue, int start, int end, int index, int valueIndex) {
    return AInputQueue_getDisplayColorTemperatureHistoryValueAtRangeValueAt((AInputQueue*)queue, start, end, index, valueIndex);
}

static void* AInputQueue_getDisplayColorTemperatureHistoryTimestampAtRangeValueAtHook(void* queue, int start, int end, int index, int valueIndex) {
    return AInputQueue
