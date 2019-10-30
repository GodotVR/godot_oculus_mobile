package org.godotengine.plugin.vr.oculus.mobile.api

/**
 * Vrapi utility functions
 */
object OvrUtilities {

    /**
     * Uses the internal left and right view matrix to compute the IPD.
     */
    @JvmStatic
    external fun getIpd(): Float

    /**
     * Sets the color multiplier for the default layer used by the VrApi compositor.
     */
    @JvmStatic external fun setDefaultLayerColorScale(
        red: Float,
        green: Float,
        blue: Float,
        alpha: Float
    ): Boolean

    @JvmStatic external fun getControllerAngularVelocity(controllerId: Int): FloatArray

    @JvmStatic external fun getControllerLinearVelocity(controllerId: Int): FloatArray

    @JvmStatic external fun getControllerAngularAcceleration(controllerId: Int): FloatArray

    @JvmStatic external fun getControllerLinearAcceleration(controllerId: Int): FloatArray

    @JvmStatic external fun getHeadAngularVelocity(): FloatArray

    @JvmStatic external fun getHeadLinearVelocity(): FloatArray

    @JvmStatic external fun getHeadAngularAcceleration(): FloatArray

    @JvmStatic external fun getHeadLinearAcceleration(): FloatArray
}