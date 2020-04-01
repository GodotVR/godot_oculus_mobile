/**
 * Provides tracking transform related apis.
 */
@file:JvmName("OvrTrackingTransform")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

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

fun OvrMobilePlugin.getTrackingSpace() = when (nativeGetTrackingSpace()) {
    TrackingSpace.LOCAL.value -> TrackingSpace.LOCAL
    TrackingSpace.LOCAL_FLOOR.value -> TrackingSpace.LOCAL_FLOOR
    TrackingSpace.LOCAL_TILTED.value -> TrackingSpace.LOCAL_TILTED
    TrackingSpace.STAGE.value -> TrackingSpace.STAGE
    TrackingSpace.LOCAL_FIXED_YAW.value -> TrackingSpace.LOCAL_FIXED_YAW
    else -> TrackingSpace.UNKNOWN
}

fun OvrMobilePlugin.setTrackingSpace(trackingSpace: TrackingSpace) =
    nativeSetTrackingSpace(trackingSpace.value)

private external fun nativeGetTrackingSpace(): Int

private external fun nativeSetTrackingSpace(trackingSpaceValue: Int): Boolean
