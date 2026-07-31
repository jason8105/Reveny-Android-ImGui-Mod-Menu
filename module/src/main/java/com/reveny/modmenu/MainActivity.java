package com.reveny.modmenu;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("RevenyNative");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initNative();
    }

    @Override
    protected void onResume() {
        super.onResume();
        renderOverlay();
    }

    @Override
    protected void onPause() {
        super.onPause();
        cleanupNative();
    }

    private native void initNative();
    private native void renderOverlay();
    private native void cleanupNative();
}
=== END FILE ===
