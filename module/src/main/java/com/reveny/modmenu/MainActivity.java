package com.reveny.modmenu;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("reveny");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initNative();
    }

    public native void initNative();
    public native String stringFromJNI();
}
=== END FILE ===
