plugins {
    id("com.android.library")
    kotlin("android")
    kotlin("android.extensions")
}

android {
    compileSdkVersion(Versions.compileSdk)
    buildToolsVersion = Versions.buildTools
    defaultConfig {
        minSdkVersion(Versions.minSdk)
        targetSdkVersion(Versions.targetSdk)
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
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk7:${Versions.kotlinVersion}")
    if (rootProject.findProject(":godot:lib") != null) {
        compileOnly(project(":godot:lib"))
    } else {
        compileOnly(fileTree(mapOf("dir" to "libs", "include" to listOf("godot-lib*.aar"))))
    }
}
