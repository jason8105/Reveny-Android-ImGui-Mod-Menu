package com.reveny.modmenu;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("reveny_mod_menu");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initModMenu();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        cleanupModMenu();
    }

    public native void initModMenu();
    public native void cleanupModMenu();
}
=== END FILE ===
