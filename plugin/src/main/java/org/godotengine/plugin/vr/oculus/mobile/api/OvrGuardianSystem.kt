package org.godotengine.plugin.vr.oculus.mobile.api

object OvrGuardianSystem {

    @JvmStatic
    external fun isBoundaryVisible(): Boolean

    @JvmStatic
    external fun requestBoundaryVisible(visible: Boolean): Boolean
}