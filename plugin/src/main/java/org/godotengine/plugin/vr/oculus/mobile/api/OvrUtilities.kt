/**
 * Vrapi utility functions
 */
@file:JvmName("OvrUtilities")

package org.godotengine.plugin.vr.oculus.mobile.api

import android.graphics.Color
import android.graphics.RectF
import android.util.Size
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

enum class OvrEye(internal val eyeIndex: Int) {
    LEFT(0),
    RIGHT(1)
}

/**
 * Uses the internal left and right view matrix to compute the IPD.
 */
fun OvrMobilePlugin.getIpd() =
    nativeGetIpd()

fun OvrMobilePlugin.getRenderTargetWidth() = nativeGetRenderTargetWidth()

fun OvrMobilePlugin.getRenderTargetHeight() = nativeGetRenderTargetHeight()

/**
 * Returns the fov for the given [OvrEye] in degrees.
 */
fun OvrMobilePlugin.getEyeFov(eye: OvrEye): RectF {
    val fovArray = nativeGetEyeFov(eye.eyeIndex)
    return RectF(fovArray[0], fovArray[3], fovArray[1], fovArray[2])
}

/**
 * Return the viewport bounds for the given [OvrEye].
 */
fun OvrMobilePlugin.getEyeViewportBounds(eye: OvrEye): RectF {
    val boundsArray = nativeGetEyeViewportBounds(eye.eyeIndex)
    return RectF(boundsArray[0], boundsArray[3], boundsArray[2], boundsArray[1])
}

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

private external fun nativeGetRenderTargetWidth(): Int

private external fun nativeGetRenderTargetHeight(): Int

private external fun nativeGetEyeFov(eye: Int): FloatArray

private external fun nativeGetEyeViewportBounds(eye: Int): FloatArray

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
