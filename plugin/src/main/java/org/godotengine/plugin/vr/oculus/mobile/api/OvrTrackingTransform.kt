package org.godotengine.plugin.vr.oculus.mobile.api

/**
 * Provides tracking transform related apis.
 */
object OvrTrackingTransform {

    /**
     * Available tracking space options.
     */
    enum class TrackingSpace(internal val value: Int) {

        /**
         * Unknown tracking space.
         */
        UNKNOWN(-1),

        /**
         * Eye level origin - controlled by system recentering
         */
        LOCAL(0),

        /**
         * Floor level origin - controlled by system recentering
         */
        LOCAL_FLOOR(1),

        /**
         * Tilted pose for "bed mode" - controlled by system recentering
         */
        LOCAL_TILTED(2),

        /**
         * Floor level origin - controlled by Guardian setup
         */
        STAGE(3),

        /**
         * Position of local space, but yaw stays constant
         */
        LOCAL_FIXED_YAW(7)
    }

    @JvmStatic
    fun getTrackingSpace() = when (nativeGetTrackingSpace()) {
        TrackingSpace.LOCAL.value -> TrackingSpace.LOCAL
        TrackingSpace.LOCAL_FLOOR.value -> TrackingSpace.LOCAL_FLOOR
        TrackingSpace.LOCAL_TILTED.value -> TrackingSpace.LOCAL_TILTED
        TrackingSpace.STAGE.value -> TrackingSpace.STAGE
        TrackingSpace.LOCAL_FIXED_YAW.value -> TrackingSpace.LOCAL_FIXED_YAW
        else -> TrackingSpace.UNKNOWN
    }

    @JvmStatic
    fun setTrackingSpace(trackingSpace: TrackingSpace) = nativeSetTrackingSpace(trackingSpace.value)

    @JvmStatic
    private external fun nativeGetTrackingSpace(): Int

    @JvmStatic
    private external fun nativeSetTrackingSpace(trackingSpaceValue: Int): Boolean

}