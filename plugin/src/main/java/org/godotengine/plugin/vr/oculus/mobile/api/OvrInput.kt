/**
 * Vrapi input functions
 */
@file:JvmName("OvrInput")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

private const val PRIMARY_CONTROLLER_ID = -1

/**
 * Specifies which controller is connected
 */
enum class ControllerType(internal val value: Int) {
    CONTROLLER_TYPE_NONE(0),

    /**
     * < LTouch in CAPI
     */
    CONTROLLER_TYPE_RESERVED_0(1 shl 0),

    /**
     * < RTouch in CAPI
     */
    CONTROLLER_TYPE_RESERVED_1(1 shl 1),
    CONTROLLER_TYPE_TRACKED_REMOTE(1 shl 2),

    /**
     * Deprecated, will be removed in a future release
     */
    CONTROLLER_TYPE_GAMEPAD(1 shl 4),
    CONTROLLER_TYPE_HAND(1 shl 5),
    CONTROLLER_TYPE_STANDARD_POINTER(1 shl 7);

    companion object {
        fun toControllerType(value: Int): ControllerType {
            for (controllerType in values()) {
                if (controllerType.value == value) {
                    return controllerType
                }
            }
            return CONTROLLER_TYPE_NONE
        }
    }
}

/**
 * Vibrate the controller at the given intensity.
 * @param controllerId Id of the controller to vibrate. Defaults to the primary controller id.
 * @param durationInMs Vibration duration in milliseconds
 * @param intensity Vibration intensity
 */
@JvmOverloads
external fun OvrMobilePlugin.vibrateController(controllerId: Int = PRIMARY_CONTROLLER_ID, durationInMs: Int, intensity: Float)

/**
 * Return the id for the primary controller.
 * Returns -1 if there is no primary controller.
 */
external fun OvrMobilePlugin.getPrimaryControllerId(): Int

/**
 * Return the [ControllerType] type of the primary controller.
 */
fun OvrMobilePlugin.getPrimaryControllerType() =
        ControllerType.toControllerType(nativeGetPrimaryControllerType())

private external fun nativeGetPrimaryControllerType(): Int
