package org.godotengine.plugin.vr.oculus.mobile

import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OculusMobileGodotPlugin(godot: Godot) : GodotPlugin(godot) {

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OculusMobile"
}