@file:JvmName("OvrGuardianSystem")

package org.godotengine.plugin.vr.oculus.mobile.api

import kotlinx.coroutines.withContext
import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

suspend fun OvrMobilePlugin.isBoundaryVisible() =
    withContext(this.glDispatcher) {
        nativeIsBoundaryVisible()
    }

suspend fun OvrMobilePlugin.requestBoundaryVisible(visible: Boolean) =
    withContext(this.glDispatcher) {
        nativeRequestBoundaryVisible(visible)
    }

private external fun nativeIsBoundaryVisible(): Boolean

private external fun nativeRequestBoundaryVisible(visible: Boolean): Boolean