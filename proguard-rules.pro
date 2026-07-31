# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.

# Keep native methods
-keepclassmembers class com.example.zygisk.imguitouch.MainActivity {
    public native void initNative();
    public native void renderOverlay();
}

# Keep JNI functions
-keepclasseswithmembernames class * {
    native <methods>;
}

# Keep native library
-keep class com.example.zygisk.imguitouch.** { *; }
