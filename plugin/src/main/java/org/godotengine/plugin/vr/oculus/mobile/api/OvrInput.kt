/**
 * Vrapi input functions
 */
@file:JvmName("OvrInput")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Vibrate the controller at the given intensity.
 * @param controllerId Id of the controller to vibrate
 * @param intensity Vibration intensity
 */
fun OvrMobilePlugin.vibrateController(controllerId: Int, intensity: Float) = nativeVibrateController(controllerId, intensity)

private external fun nativeVibrateController(controllerId: Int, intensity: Float)