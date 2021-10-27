package org.godotengine.plugin.vr.oculus.mobile.demo

import java.util.Collections
import org.godotengine.godot.FullScreenGodotApp
import org.godotengine.godot.xr.XRMode

class MainActivity : FullScreenGodotApp() {

    // Override the engine starting parameters to indicate we want VR mode.
    override fun getCommandLine(): List<String> {
        return if (BuildConfig.FLAVOR == "ovr") {
            listOf(XRMode.OVR.cmdLineArg)
        } else {
            Collections.emptyList()
        }
    }
}
