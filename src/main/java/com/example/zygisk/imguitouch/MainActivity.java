package com.example.zygisk.imguitouch;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("zygisk_imgui_touch");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Button btnInit = findViewById(R.id.btn_init);
        btnInit.setOnClickListener(v -> {
            initNative();
            Toast.makeText(this, "Native initialized", Toast.LENGTH_SHORT).show();
        });
    }

    public native void initNative();
    public native void renderOverlay();
}
