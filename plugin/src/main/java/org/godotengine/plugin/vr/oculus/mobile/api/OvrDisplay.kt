@file:JvmName("OvrDisplay")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

fun OvrMobilePlugin.getSupportedDisplayRefreshRates() = nativeGetSupportedDisplayRefreshRates()

fun OvrMobilePlugin.setDisplayRefreshRate(refreshRate: Float) = nativeSetDisplayRefreshRate(refreshRate)

private external fun nativeSetDisplayRefreshRate(refreshRate: Float): Boolean

private external fun nativeGetSupportedDisplayRefreshRates(): FloatArray
