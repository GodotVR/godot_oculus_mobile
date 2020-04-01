plugins {
    id("com.android.library")
    kotlin("android")
    kotlin("android.extensions")
}

android {
    compileSdkVersion(29)
    buildToolsVersion = "29.0.1"
    defaultConfig {
        minSdkVersion(18)
        targetSdkVersion(29)
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

    ndkVersion = "21.0.6113669"

    externalNativeBuild {
        cmake {
            setPath("CMakeLists.txt")
        }
    }
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk7:1.3.70")
    if (rootProject.findProject(":godot:lib") != null) {
        compileOnly(project(":godot:lib"))
    } else {
        compileOnly(fileTree(mapOf("dir" to "libs", "include" to listOf("godot-lib*.aar"))))
    }
}
