@file:JvmName("OvrMobilePlugin")

package org.godotengine.plugin.vr.oculus.mobile

import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin
import java.util.concurrent.ConcurrentLinkedQueue

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OvrMobilePlugin(godot: Godot) : GodotPlugin(godot) {

    /**
     * Used to inquire about the headset state.
     */
    interface HeadsetStateListener {
        /**
         * Notifies when the headset is mounted.
         */
        fun onHeadsetMounted()

        /**
         * Notifies when the headset is unmounted.
         */
        fun onHeadsetUnmounted()
    }

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }
    }

    private val headsetStateListeners = ConcurrentLinkedQueue<HeadsetStateListener>()

    override fun getPluginGDNativeLibrariesPaths() =
        setOf("addons/godot_ovrmobile/godot_ovrmobile.gdnlib")

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OVRMobile"

    override fun onGLGodotMainLoopStarted() {
        super.onGLGodotMainLoopStarted()
        initializeWrapper()
    }

    override fun onMainDestroy() {
        super.onMainDestroy()
        runOnGLThread {
            uninitializeWrapper()
        }
    }

    fun registerHeadsetStateListener(listener: HeadsetStateListener) {
        headsetStateListeners.add(listener)
    }

    fun unregisterHeadsetStateListener(listener: HeadsetStateListener) {
        headsetStateListeners.remove(listener)
    }

    /**
     * Invoked by the native code to signal the headset is mounted.
     */
    private fun onHeadsetMounted() {
        // TODO(m4gr3d): Emit headset mounted signal when https://github.com/godotengine/godot/pull/37305 is submitted.
        for (listener in headsetStateListeners) {
            listener.onHeadsetMounted()
        }
    }

    /**
     * Invoked by the native code to signal the headset is unmounted.
     */
    private fun onHeadsetUnmounted() {
        // TODO(m4gr3d): Emit headset unmounted signal when https://github.com/godotengine/godot/pull/37305 is submitted.
        for (listener in headsetStateListeners) {
            listener.onHeadsetUnmounted()
        }
    }

    private external fun initializeWrapper()

    private external fun uninitializeWrapper()
}