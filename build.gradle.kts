// Top-level build file where you can add configuration options common to all sub-projects/modules.

buildscript {
    repositories {
        google()
        jcenter()

    }
    dependencies {
        classpath("com.android.tools.build:gradle:3.5.0")
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:1.3.50")
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
 * Generate the native shared libraries the plugin depends on.
 */
tasks.register<Copy>("generateSharedLibs") {
    dependsOn(":plugin:externalNativeBuildDebug")
    dependsOn(":plugin:externalNativeBuildRelease")

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

/**
 * Generate the plugin binaries.
 */
tasks.register<Copy>("generatePluginBinary") {
    dependsOn(":plugin:assembleDebug")
    dependsOn(":plugin:assembleRelease")
    from("plugin/build/outputs/aar")
    into("$outputDir/pluginBin")
}