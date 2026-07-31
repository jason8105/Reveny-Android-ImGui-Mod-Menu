package com.reveny.modmenu;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("RevenyModMenu");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initModMenu();
    }

    public native void initModMenu();
    public native void renderOverlay();
}
=== END FILE ===
