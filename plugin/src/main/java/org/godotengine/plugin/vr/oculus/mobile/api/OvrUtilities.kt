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
fun OvrMobilePlugin.getIpd(): Float {
    return if (isSharedLibLoaded()) {
        nativeGetIpd()
    } else {
        0F
    }
}

fun OvrMobilePlugin.getRenderTargetWidth(): Int {
   return if (isSharedLibLoaded()) {
       nativeGetRenderTargetWidth()
   } else {
       1024
   }
}

fun OvrMobilePlugin.getRenderTargetHeight(): Int {
    return if (isSharedLibLoaded()) {
        nativeGetRenderTargetHeight()
    } else {
        1024
    }
}

/**
 * Returns the fov for the given [OvrEye] in degrees.
 */
fun OvrMobilePlugin.getEyeFov(eye: OvrEye): RectF {
    if (isSharedLibLoaded()) {
        val fovArray = nativeGetEyeFov(eye.eyeIndex)
        return RectF(fovArray[0], fovArray[3], fovArray[1], fovArray[2])
    } else {
        return RectF()
    }
}

/**
 * Return the viewport bounds for the given [OvrEye].
 */
fun OvrMobilePlugin.getEyeViewportBounds(eye: OvrEye): RectF {
    if (isSharedLibLoaded()) {
        val boundsArray = nativeGetEyeViewportBounds(eye.eyeIndex)
        return RectF(boundsArray[0], boundsArray[3], boundsArray[2], boundsArray[1])
    } else {
        return RectF()
    }
}

fun OvrMobilePlugin.setDefaultLayerColorScale(color: Int): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetDefaultLayerColorScale(
            Color.red(color).toFloat(),
            Color.green(color).toFloat(),
            Color.blue(color).toFloat(),
            Color.alpha(color).toFloat()
        )
    } else {
        false
    }
}

fun OvrMobilePlugin.getControllerAngularVelocity(controllerId: Int): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetControllerAngularVelocity(controllerId)
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getControllerLinearVelocity(controllerId: Int): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetControllerLinearVelocity(controllerId)
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getControllerAngularAcceleration(controllerId: Int): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetControllerAngularAcceleration(controllerId)
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getControllerLinearAcceleration(controllerId: Int): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetControllerLinearAcceleration(controllerId)
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getHeadAngularVelocity(): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetHeadAngularVelocity()
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getHeadLinearVelocity(): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetHeadLinearVelocity()
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getHeadAngularAcceleration(): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetHeadAngularAcceleration()
    } else {
        floatArrayOf()
    }
}

fun OvrMobilePlugin.getHeadLinearAcceleration(): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetHeadLinearAcceleration()
    } else {
        floatArrayOf()
    }
}

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
