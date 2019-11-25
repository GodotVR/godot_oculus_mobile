/**
 * Vrapi utility functions
 */
@file:JvmName("OvrUtilities")

package org.godotengine.plugin.vr.oculus.mobile.api

import android.graphics.Color
import androidx.annotation.ColorInt
import kotlinx.coroutines.withContext
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Uses the internal left and right view matrix to compute the IPD.
 */
suspend fun OvrMobilePlugin.getIpd() = withContext(this.glDispatcher) {
    nativeGetIpd()
}

suspend fun OvrMobilePlugin.setDefaultLayerColorScale(@ColorInt color: Int) =
    withContext(this.glDispatcher) {
        nativeSetDefaultLayerColorScale(
            Color.red(color).toFloat(),
            Color.green(color).toFloat(),
            Color.blue(color).toFloat(),
            Color.alpha(color).toFloat()
        )
    }

suspend fun OvrMobilePlugin.getControllerAngularVelocity(controllerId: Int) = withContext(this.glDispatcher) {
    nativeGetControllerAngularVelocity(controllerId)
}

suspend fun OvrMobilePlugin.getControllerLinearVelocity(controllerId: Int) = withContext(this.glDispatcher) {
    nativeGetControllerLinearVelocity(controllerId)
}

suspend fun OvrMobilePlugin.getControllerAngularAcceleration(controllerId: Int) = withContext(this.glDispatcher) {
    nativeGetControllerAngularAcceleration(controllerId)
}

suspend fun OvrMobilePlugin.getControllerLinearAcceleration(controllerId: Int) = withContext(this.glDispatcher) {
    nativeGetControllerLinearAcceleration(controllerId)
}

suspend fun OvrMobilePlugin.getHeadAngularVelocity() = withContext(this.glDispatcher) {
    nativeGetHeadAngularVelocity()
}

suspend fun OvrMobilePlugin.getHeadLinearVelocity() = withContext(this.glDispatcher) {
    nativeGetHeadLinearVelocity()
}

suspend fun OvrMobilePlugin.getHeadAngularAcceleration() = withContext(this.glDispatcher) {
    nativeGetHeadAngularAcceleration()
}

suspend fun OvrMobilePlugin.getHeadLinearAcceleration() = withContext(this.glDispatcher) {
    nativeGetHeadLinearAcceleration()
}

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