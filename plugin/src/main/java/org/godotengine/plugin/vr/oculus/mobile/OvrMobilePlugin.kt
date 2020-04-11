@file:JvmName("OvrMobilePlugin")

package org.godotengine.plugin.vr.oculus.mobile

import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin
import org.godotengine.godot.plugin.SignalInfo
import java.util.concurrent.ConcurrentLinkedQueue
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * Driver class for the Oculus Mobile Godot plugin.
 */
class OvrMobilePlugin(godot: Godot) : GodotPlugin(godot) {

    /**
     * Used to listen to events dispatched by the OVRMobile plugin.
     */
    interface OvrEventListener {
        /**
         * Notifies when the headset is mounted.
         */
        fun onHeadsetMounted()

        /**
         * Notifies when the headset is unmounted.
         */
        fun onHeadsetUnmounted()

        /**
         * Notifies when the input focus is gained.
         */
        fun onInputFocusGained()

        /**
         * Notifies when the input focus is lost.
         */
        fun onInputFocusLost()

        /**
         * Notifies when the plugin enters VR mode.
         */
        fun onEnterVrMode()

        /**
         * Notifies when the plugin leaves VR mode.
         */
        fun onLeaveVrMode()
    }

    companion object {
        init {
            System.loadLibrary("godot_ovrmobile")
        }

        // Set of plugin signals
        private val HEADSET_MOUNTED_SIGNAL = SignalInfo("HeadsetMounted")
        private val HEADSET_UNMOUNTED_SIGNAL = SignalInfo("HeadsetUnmounted")
        private val INPUT_FOCUS_GAINED_SIGNAL = SignalInfo("InputFocusGained")
        private val INPUT_FOCUS_LOST_SIGNAL = SignalInfo("InputFocusLost")
        private val ENTER_VR_MODE_SIGNAL = SignalInfo("EnterVrMode")
        private val LEAVE_VR_MODE_SIGNAL = SignalInfo("LeaveVrMode")
    }

    private val ovrEventListeners = ConcurrentLinkedQueue<OvrEventListener>()

    override fun getPluginGDNativeLibrariesPaths() =
        setOf("addons/godot_ovrmobile/godot_ovrmobile.gdnlib")

    override fun getPluginMethods() = listOf<String>()

    override fun getPluginName() = "OVRMobile"

    override fun getPluginSignals() = mutableSetOf(
        HEADSET_MOUNTED_SIGNAL,
        HEADSET_UNMOUNTED_SIGNAL,
        INPUT_FOCUS_GAINED_SIGNAL,
        INPUT_FOCUS_LOST_SIGNAL,
        ENTER_VR_MODE_SIGNAL,
        LEAVE_VR_MODE_SIGNAL
    )

    override fun onGLSurfaceCreated(gl: GL10, config: EGLConfig) {
        super.onGLSurfaceCreated(gl, config)
        initializeWrapper()
    }

    override fun onMainDestroy() {
        super.onMainDestroy()
        runOnGLThread {
            uninitializeWrapper()
        }
    }

    fun registerOvrEventListener(listener: OvrEventListener) {
        ovrEventListeners.add(listener)
    }

    fun unregisterOvrEventListener(listener: OvrEventListener) {
        ovrEventListeners.remove(listener)
    }

    /**
     * Invoked by the native code to signal the headset is mounted.
     */
    private fun onHeadsetMounted() {
        // Emit headset mounted signal.
        emitSignal(HEADSET_MOUNTED_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onHeadsetMounted()
        }
    }

    /**
     * Invoked by the native code to signal the headset is unmounted.
     */
    private fun onHeadsetUnmounted() {
        // Emit headset unmounted signal.
        emitSignal(HEADSET_UNMOUNTED_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onHeadsetUnmounted()
        }
    }

    /**
     * Invoked by the native code to signal input focus gain.
     */
    private fun onInputFocusGained() {
        // Emit input focus gained signal.
        emitSignal(INPUT_FOCUS_GAINED_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onInputFocusGained()
        }
    }

    /**
     * Invoked by the native code to signal input focus loss.
     */
    private fun onInputFocusLost() {
        // Emit input focus lost signal.
        emitSignal(INPUT_FOCUS_LOST_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onInputFocusLost()
        }
    }

    private fun onEnterVrMode() {
        // Emit enter vr mode signal.
        emitSignal(ENTER_VR_MODE_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onEnterVrMode()
        }
    }

    private fun onLeaveVrMode() {
        // Emit leave vr mode signal.
        emitSignal(LEAVE_VR_MODE_SIGNAL.name)
        for (listener in ovrEventListeners) {
            listener.onLeaveVrMode()
        }
    }

    private external fun initializeWrapper()

    private external fun uninitializeWrapper()
}