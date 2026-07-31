package com.reveny.modmenu;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.widget.FrameLayout;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("RevenyModMenu");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initImGui();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        shutdownImGui();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            hookTouch();
        }
        return super.onTouchEvent(event);
    }

    public native void hookTouch();
    public native void unhookTouch();
    public native void setImGuiPos(float x, float y);
    public native void setImGuiSize(float width, float height);
    public native void initImGui();
    public native void shutdownImGui();
}
=== END FILE ===
