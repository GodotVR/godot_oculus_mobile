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

    /**
     * Used to query input focus state.
     */
    interface InputFocusListener {
        /**
         * Notifies when the input focus is gained.
         */
        fun onInputFocusGained()

        /**
         * Notifies when the input focus is lost.
         */
        fun onInputFocusLost()
    }

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }
    }

    private val headsetStateListeners = ConcurrentLinkedQueue<HeadsetStateListener>()
    private val inputFocusListeners = ConcurrentLinkedQueue<InputFocusListener>()

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

    fun registerInputFocusListener(listener: InputFocusListener) {
        inputFocusListeners.add(listener)
    }

    fun unregisterInputFocusListener(listener: InputFocusListener) {
        inputFocusListeners.remove(listener)
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

    /**
     * Invoked by the native code to signal input focus gain.
     */
    private fun onInputFocusGained() {
        // TODO(m4gr3d): Emit signal when https://github.com/godotengine/godot/pull/37305 is submitted.
        for (listener in inputFocusListeners) {
            listener.onInputFocusGained()
        }
    }

    /**
     * Invoked by the native code to signal input focus loss.
     */
    private fun onInputFocusLost() {
        // TODO(m4gr3d): Emit signal when https://github.com/godotengine/godot/pull/37305 is submitted.
        for (listener in inputFocusListeners) {
            listener.onInputFocusLost()
        }
    }

    private external fun initializeWrapper()

    private external fun uninitializeWrapper()
}