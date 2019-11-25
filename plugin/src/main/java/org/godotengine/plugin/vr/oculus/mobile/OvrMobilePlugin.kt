package org.godotengine.plugin.vr.oculus.mobile

import kotlinx.coroutines.asCoroutineDispatcher
import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin
import java.util.concurrent.Executor

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OvrMobilePlugin(godot: Godot) : GodotPlugin(godot) {

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }
    }

    internal val glDispatcher = object : Executor {
        override fun execute(command: Runnable) {
            runOnGLThread(command)
        }
    }.asCoroutineDispatcher()

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OVRMobile"
}