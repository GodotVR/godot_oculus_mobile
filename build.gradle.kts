// Top-level build file where you can add configuration options common to all sub-projects/modules.

buildscript {
    repositories {
        google()
        jcenter()

    }
    dependencies {
        classpath("com.android.tools.build:gradle:3.5.3")
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlinVersion}")
        // NOTE: Do not place your application dependencies here; they belong
        // in the individual module build.gradle files
    }
}

allprojects {
    repositories {
        google()
        jcenter()

    }
}

val outputDir = "build/outputs"

tasks.register<Delete>("clean") {
    delete(rootProject.buildDir)

    // Delete the contents of the outputs directory.
    delete(outputDir)
}

/**
 * Generate the plugin binaries.
 */
tasks.register<Copy>("generatePluginBinary") {
    dependsOn(":OVRMobile:assembleDebug")
    dependsOn(":OVRMobile:assembleRelease")
    from("plugin/build/outputs/aar")
    into("$outputDir/pluginBin")
}

/**
 * Generate the plugin native shared libraries.
 * This is mostly to be used by maintainers to update the https://github.com/GodotVR/godot-oculus-mobile-asset repo.
 */
tasks.register<Copy>("generateSharedLibs") {
    dependsOn(":OVRMobile:externalNativeBuildDebug")
    dependsOn(":OVRMobile:externalNativeBuildRelease")

    // Specify the base directory. All following 'into' targets will be relative
    // to this directory.
    into("$outputDir/sharedLibs")

    // Copy the generated debug shared libs into the outputs directory
    from("plugin/build/intermediates/cmake/debug/obj") {
        into("debug")
    }

    // Copy the generated release shared libs into the outputs directory
    from("plugin/build/intermediates/cmake/release/obj") {
        into("release")
    }
}
