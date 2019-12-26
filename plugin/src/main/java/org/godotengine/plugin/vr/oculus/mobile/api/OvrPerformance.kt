/**
 * Wrapper for the VrApi performance apis.
 */
@file:JvmName("OvrPerformance")

package org.godotengine.plugin.vr.oculus.mobile.api

import kotlinx.coroutines.withContext
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

suspend fun OvrMobilePlugin.setClockLevels(cpuLevel: Int, gpuLevel: Int) =
    withContext(this.glDispatcher) {
        nativeSetClockLevels(cpuLevel, gpuLevel)
    }

suspend fun OvrMobilePlugin.setExtraLatencyMode(latencyMode: Int) =
    withContext(this.glDispatcher) {
        nativeSetExtraLatencyMode(latencyMode)
    }

suspend fun OvrMobilePlugin.setFoveationLevel(foveationLevel: Int) =
    withContext(this.glDispatcher) {
        nativeSetFoveationLevel(foveationLevel)
    }

suspend fun OvrMobilePlugin.setSwapInterval(swapInterval: Int) =
    withContext(this.glDispatcher) {
        nativeSetSwapInterval(swapInterval)
    }

private external fun nativeSetClockLevels(cpuLevel: Int, gpuLevel: Int): Boolean

private external fun nativeSetExtraLatencyMode(latencyMode: Int): Boolean

private external fun nativeSetFoveationLevel(foveationLevel: Int): Boolean

private external fun nativeSetSwapInterval(swapInterval: Int): Boolean