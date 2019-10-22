/**
 * Wrapper for the VrApi performance apis.
 */
@file:JvmName("OvrPerformance")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

fun OvrMobilePlugin.setClockLevels(cpuLevel: Int, gpuLevel: Int) =
    nativeSetClockLevels(cpuLevel, gpuLevel)

fun OvrMobilePlugin.setExtraLatencyMode(latencyMode: Int) = nativeSetExtraLatencyMode(latencyMode)

fun OvrMobilePlugin.setFoveationLevel(foveationLevel: Int) = nativeSetFoveationLevel(foveationLevel)

fun OvrMobilePlugin.setSwapInterval(swapInterval: Int) = nativeSetSwapInterval(swapInterval)

private external fun nativeSetClockLevels(cpuLevel: Int, gpuLevel: Int): Boolean

private external fun nativeSetExtraLatencyMode(latencyMode: Int): Boolean

private external fun nativeSetFoveationLevel(foveationLevel: Int): Boolean

private external fun nativeSetSwapInterval(swapInterval: Int): Boolean