package org.godotengine.plugin.vr.oculus.mobile.api

object OvrDisplayRefreshRate {

    @JvmStatic
    external fun setDisplayRefreshRate(refreshRate: Float): Boolean

    @JvmStatic
    external fun getSupportedDisplayRefreshRates(): FloatArray
}