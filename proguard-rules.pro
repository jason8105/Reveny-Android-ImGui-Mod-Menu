# Add project specific ProGuard rules here.
-keep class com.example.mod.** { *; }
-keep class com.example.mod.** { *; }

# Keep native methods
-keepclasseswithmembernames class * {
    native <methods>;
}

# Keep JNI methods
-keepclasseswithmembers class * {
    public static native *;
}

=== END FILE ===
