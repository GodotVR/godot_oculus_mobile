plugins {
    id("com.android.library")
    kotlin("android")
    kotlin("android.extensions")
}

android {
    compileSdkVersion(28)
    buildToolsVersion = "29.0.1"
    defaultConfig {
        minSdkVersion(24)
        targetSdkVersion(28)
        versionName = "1.0"
        versionCode = 1
        externalNativeBuild {
            cmake {
                cppFlags +=  "-std=c++14"
            }
        }
        ndk {
            abiFilters("arm64-v8a", "armeabi-v7a")
        }
    }

    externalNativeBuild {
        cmake {
            setPath("CMakeLists.txt")
        }
    }
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk7:1.3.50")
    compileOnly(fileTree(mapOf("dir" to "libs", "include" to listOf("*.aar"))))
}
