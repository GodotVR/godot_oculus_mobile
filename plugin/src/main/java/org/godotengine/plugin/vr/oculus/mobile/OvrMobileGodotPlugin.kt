package org.godotengine.plugin.vr.oculus.mobile

import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OvrMobileGodotPlugin(godot: Godot) : GodotPlugin(godot) {

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }
    }

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OVRMobile"
}