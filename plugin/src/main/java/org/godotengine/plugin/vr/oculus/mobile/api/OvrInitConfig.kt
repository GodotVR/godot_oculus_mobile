/**
 * Used to access and setup the init parameters for the plugin.
 *
 * The methods defined in this class must be invoked prior to initializing the Oculus mobile plugin.
 */
@file:JvmName("OvrInitConfig")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Set the factor by which to multiply the recommended render target size for the app.
 */
fun OvrMobilePlugin.setRenderTargetSizeMultiplier(multiplier: Double): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetRenderTargetSizeMultiplier(multiplier)
    } else {
        false
    }
}

private external fun nativeSetRenderTargetSizeMultiplier(multiplier: Double): Boolean
