package org.godotengine.plugin.vr.oculus.mobile.api

/**
 * Wrapper for the VrApi performance apis.
 */
object OvrPerformance {

    @JvmStatic
    external fun setClockLevels(cpuLevel: Int, gpuLevel: Int): Boolean

    @JvmStatic
    external fun setExtraLatencyMode(latencyMode: Int): Boolean

    @JvmStatic
    external fun setFoveationLevel(foveationLevel: Int): Boolean

    @JvmStatic
    external fun setSwapInterval(swapInterval: Int): Boolean
}