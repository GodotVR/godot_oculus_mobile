@file:JvmName("OvrMobilePlugin")

package org.godotengine.plugin.vr.oculus.mobile

import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OvrMobilePlugin(godot: Godot) : GodotPlugin(godot) {

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }
    }

    override fun getPluginGDNativeLibrariesPaths() =
        setOf("addons/godot_ovrmobile/godot_ovrmobile.gdnlib")

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OVRMobile"
}