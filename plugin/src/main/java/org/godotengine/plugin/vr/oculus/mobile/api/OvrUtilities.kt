/**
 * Vrapi utility functions
 */
@file:JvmName("OvrUtilities")

package org.godotengine.plugin.vr.oculus.mobile.api

import android.graphics.Color
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Uses the internal left and right view matrix to compute the IPD.
 */
fun OvrMobilePlugin.getIpd() =
    nativeGetIpd()

fun OvrMobilePlugin.setDefaultLayerColorScale(color: Int) =
    nativeSetDefaultLayerColorScale(
        Color.red(color).toFloat(),
        Color.green(color).toFloat(),
        Color.blue(color).toFloat(),
        Color.alpha(color).toFloat()
    )

fun OvrMobilePlugin.getControllerAngularVelocity(controllerId: Int) =
    nativeGetControllerAngularVelocity(controllerId)

fun OvrMobilePlugin.getControllerLinearVelocity(controllerId: Int) =
    nativeGetControllerLinearVelocity(controllerId)

fun OvrMobilePlugin.getControllerAngularAcceleration(controllerId: Int) =
    nativeGetControllerAngularAcceleration(controllerId)

fun OvrMobilePlugin.getControllerLinearAcceleration(controllerId: Int) =
    nativeGetControllerLinearAcceleration(controllerId)

fun OvrMobilePlugin.getHeadAngularVelocity() =
    nativeGetHeadAngularVelocity()

fun OvrMobilePlugin.getHeadLinearVelocity() =
    nativeGetHeadLinearVelocity()

fun OvrMobilePlugin.getHeadAngularAcceleration() =
    nativeGetHeadAngularAcceleration()

fun OvrMobilePlugin.getHeadLinearAcceleration() =
    nativeGetHeadLinearAcceleration()

private external fun nativeGetIpd(): Float

/**
 * Sets the color multiplier for the default layer used by the VrApi compositor.
 */
private external fun nativeSetDefaultLayerColorScale(
    red: Float,
    green: Float,
    blue: Float,
    alpha: Float
): Boolean

private external fun nativeGetControllerAngularVelocity(controllerId: Int): FloatArray

private external fun nativeGetControllerLinearVelocity(controllerId: Int): FloatArray

private external fun nativeGetControllerAngularAcceleration(controllerId: Int): FloatArray

private external fun nativeGetControllerLinearAcceleration(controllerId: Int): FloatArray

private external fun nativeGetHeadAngularVelocity(): FloatArray

private external fun nativeGetHeadLinearVelocity(): FloatArray

private external fun nativeGetHeadAngularAcceleration(): FloatArray

private external fun nativeGetHeadLinearAcceleration(): FloatArray