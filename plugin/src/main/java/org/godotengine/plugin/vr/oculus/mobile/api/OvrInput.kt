/**
 * Vrapi input functions
 */
@file:JvmName("OvrInput")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

private const val PRIMARY_CONTROLLER_ID = -1

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
