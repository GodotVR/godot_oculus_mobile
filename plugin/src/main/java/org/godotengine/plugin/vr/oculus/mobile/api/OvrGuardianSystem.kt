@file:JvmName("OvrGuardianSystem")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

fun OvrMobilePlugin.isBoundaryVisible(): Boolean {
    return if (isSharedLibLoaded()) {
        nativeIsBoundaryVisible()
    } else {
        false
    }
}

fun OvrMobilePlugin.requestBoundaryVisible(visible: Boolean): Boolean {
    return if (isSharedLibLoaded()) {
        nativeRequestBoundaryVisible(visible)
    } else {
        false
    }
}

private external fun nativeIsBoundaryVisible(): Boolean

private external fun nativeRequestBoundaryVisible(visible: Boolean): Boolean
