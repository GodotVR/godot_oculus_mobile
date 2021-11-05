/**
 * Wrapper for the VrApi performance apis.
 */
@file:JvmName("OvrPerformance")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Extra latency mode pipelines app CPU work a frame ahead of VR composition.
 */
enum class ExtraLatencyMode(internal val value: Int) {
    OFF(0),
    ON(1),
    DYNAMIC(2);
}

/**
 * Used to control swapchain foveation levels.
 */
enum class FoveationLevel(internal val value: Int) {
    NONE(0),
    LOW(1),
    MEDIUM(2),
    HIGH(3),
    HIGH_TOP(4);
}

/**
 * Set the CPU and GPU performance levels.
 * Increasing the levels increases performance at the cost of higher power consumption
 * which likely leads to a greater chance of overheating.
 *
 * Levels will be clamped to the expected range.
 * Default clock levels are cpuLevel = 2, gpuLevel = 2.
 */
fun OvrMobilePlugin.setClockLevels(cpuLevel: Int, gpuLevel: Int): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetClockLevels(cpuLevel, gpuLevel)
    } else {
        false
    }
}

/**
 * If [ExtraLatencyMode.ON] specified, adds an extra frame of latency for full GPU
 * utilization. Default is [ExtraLatencyMode.OFF].
 */
fun OvrMobilePlugin.setExtraLatencyMode(latencyMode: ExtraLatencyMode): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetExtraLatencyMode(latencyMode.value)
    } else {
        false
    }
}

/**
 * Set the fixed foveated rendering level if it's available.
 * Returns true if it's available and the given level is valid, false otherwise.
 *
 * **Note:** Dynamic foveation should be used instead.
 *
 * [Additional docs](https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/)
 */
fun OvrMobilePlugin.setFoveationLevel(foveationLevel: FoveationLevel): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetFoveationLevel(foveationLevel.value)
    } else {
        false
    }
}

/**
 * Sets the swap interval to control the application frame timing.
 *
 * [Additional docs](https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing)
 */
fun OvrMobilePlugin.setSwapInterval(swapInterval: Int): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetSwapInterval(swapInterval)
    } else {
        false
    }
}

/**
 * Enable dynamic foveation.
 *
 * [Additional docs](https://developer.oculus.com/documentation/native/android/mobile-ffr/)
 */
fun OvrMobilePlugin.enableDynamicFoveation(enable: Boolean): Boolean {
    return if (isSharedLibLoaded()) {
        nativeEnableDynamicFoveation(enable)
    } else {
        false
    }
}

private external fun nativeEnableDynamicFoveation(enable: Boolean): Boolean

private external fun nativeSetClockLevels(cpuLevel: Int, gpuLevel: Int): Boolean

private external fun nativeSetExtraLatencyMode(latencyMode: Int): Boolean

private external fun nativeSetFoveationLevel(foveationLevel: Int): Boolean

private external fun nativeSetSwapInterval(swapInterval: Int): Boolean
