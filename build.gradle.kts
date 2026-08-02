plugins {
id("com.android.application")
id("org.jetbrains.kotlin.android")
}
android {
namespace = "com.reveny.modmenu"
compileSdk = 33
Copy code
defaultConfig {
    applicationId = "com.reveny.modmenu"
    minSdk = 29
    targetSdk = 33
    versionCode = 1
    versionName = "1.0"

    testInstrumentationRunner = "androidx.test
