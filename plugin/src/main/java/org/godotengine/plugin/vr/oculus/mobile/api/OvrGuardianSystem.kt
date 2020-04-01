@file:JvmName("OvrGuardianSystem")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

fun OvrMobilePlugin.isBoundaryVisible() = nativeIsBoundaryVisible()

fun OvrMobilePlugin.requestBoundaryVisible(visible: Boolean) = nativeRequestBoundaryVisible(visible)

private external fun nativeIsBoundaryVisible(): Boolean

private external fun nativeRequestBoundaryVisible(visible: Boolean): Boolean