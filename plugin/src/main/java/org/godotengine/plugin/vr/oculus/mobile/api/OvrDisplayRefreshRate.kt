@file:JvmName("OvrDisplayRefreshRate")

package org.godotengine.plugin.vr.oculus.mobile.api

import kotlinx.coroutines.withContext
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

suspend fun OvrMobilePlugin.getSupportedDisplayRefreshRates() =
    withContext(this.glDispatcher) {
        nativeGetSupportedDisplayRefreshRates()
    }

suspend fun OvrMobilePlugin.setDisplayRefreshRate(refreshRate: Float) =
    withContext(this.glDispatcher) {
        nativeSetDisplayRefreshRate(refreshRate)
    }

private external fun nativeSetDisplayRefreshRate(refreshRate: Float): Boolean

private external fun nativeGetSupportedDisplayRefreshRates(): FloatArray