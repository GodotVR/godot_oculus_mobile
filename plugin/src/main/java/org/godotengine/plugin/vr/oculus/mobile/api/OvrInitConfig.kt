package org.godotengine.plugin.vr.oculus.mobile.api

/**
 * Used to access and setup the init parameters for the plugin.
 *
 * The methods defined in this class must be invoked prior to initializing the Oculus mobile plugin.
 */
object OvrInitConfig {

    /**
     * Set the factor by which to multiply the recommended render target size for the app.
     */
    @JvmStatic external fun setRenderTargetSizeMultiplier(multiplier: Double) : Boolean
}