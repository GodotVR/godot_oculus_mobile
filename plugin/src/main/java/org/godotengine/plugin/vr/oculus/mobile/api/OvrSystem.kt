@file:JvmName("OvrSystem")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Oculus device type.
 */
enum class DeviceType(internal val rangeStart: Int, internal val rangeEnd: Int = rangeStart) {
    /**
     * Unknwon device type.
     */
    UNKNOWN(-1),

    /**
     * Device type for the Oculus Quest 1.
     */
    OCULUS_QUEST(256, 319),

    /**
     * Device type for the Oculus Quest 2.
     */
    OCULUS_QUEST2(320, 383);

    companion object {
        fun toDeviceType(value: Int): DeviceType {
            for(deviceType in values()) {
                if (deviceType.rangeStart <= value && value <= deviceType.rangeEnd) {
                    return deviceType;
                }
            }
            return UNKNOWN
        }
    }
}

/**
 * Return the current [DeviceType] type.
 */
fun OvrMobilePlugin.getDeviceType() = DeviceType.toDeviceType(nativeGetDeviceType())

private external fun nativeGetDeviceType(): Int
