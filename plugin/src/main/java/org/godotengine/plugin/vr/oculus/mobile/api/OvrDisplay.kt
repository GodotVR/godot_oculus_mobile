@file:JvmName("OvrDisplay")

package org.godotengine.plugin.vr.oculus.mobile.api

import org.godotengine.plugin.vr.oculus.mobile.OvrMobilePlugin

/**
 * Color space types for HMDs
 * @see https://developer.oculus.com/documentation/native/android/mobile-colorspace/
 */
enum class ColorSpace(internal val value: Int) {
    /** No color correction, not recommended for production use. See notes above for more info */
    COLOR_SPACE_UNMANAGED(0),

    /** Preferred color space for standardized color across all Oculus HMDs with D65 white point */
    COLOR_SPACE_REC_2020(1),

    /** Rec. 709 is used on Oculus Go and shares the same primary color coordinates as sRGB */
    COLOR_SPACE_REC_709(2),

    /** Oculus Rift CV1 uses a unique color space, see enum description for more info */
    COLOR_SPACE_RIFT_CV1(3),

    /** Oculus Rift S uses a unique color space, see enum description for more info */
    COLOR_SPACE_RIFT_S(4),

    /** Oculus Quest's native color space is slightly different than Rift CV1 */
    COLOR_SPACE_QUEST(5),

    /** Similar to DCI-P3. See notes above for more details on P3 */
    COLOR_SPACE_P3(6),

    /** Similar to sRGB but with deeper greens using D65 white point */
    COLOR_SPACE_ADOBE_RGB(7);

    companion object {
        fun toColorSpace(value: Int): ColorSpace {
            for (colorSpace in values()) {
                if (colorSpace.value == value) {
                    return colorSpace
                }
            }
            return COLOR_SPACE_UNMANAGED
        }
    }
}

/**
 * Used to retrieve the device color space.
 * This is a constant for each device type.
 * @see https://developer.oculus.com/documentation/native/android/mobile-colorspace/
 */
fun OvrMobilePlugin.getColorSpace(): ColorSpace {
    return if (isSharedLibLoaded()) {
        ColorSpace.toColorSpace(nativeGetColorSpace())
    } else {
        ColorSpace.COLOR_SPACE_UNMANAGED
    }
}

/**
 * Used to update the device color space.
 *
 * @param[colorSpace] The new target color space.
 * @return True if the device's color space was updated, false otherwise.
 */
fun OvrMobilePlugin.setColorSpace(colorSpace: ColorSpace): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetColorSpace(colorSpace.value)
    } else {
        false
    }
}

/**
 * Used to access the display refresh rates supported by the device.
 */
fun OvrMobilePlugin.getSupportedDisplayRefreshRates(): FloatArray {
    return if (isSharedLibLoaded()) {
        nativeGetSupportedDisplayRefreshRates()
    } else {
        floatArrayOf()
    }
}

/**
 * Used to update the device display refresh rate.
 *
 * @param[refreshRate] Target refresh rate. Must be one of the supported values returned by
 * [getSupportedDisplayRefreshRates].
 */
fun OvrMobilePlugin.setDisplayRefreshRate(refreshRate: Float): Boolean {
    return if (isSharedLibLoaded()) {
        nativeSetDisplayRefreshRate(refreshRate)
    } else {
        false
    }
}

private external fun nativeSetColorSpace(colorSpace: Int): Boolean

private external fun nativeGetColorSpace(): Int

private external fun nativeSetDisplayRefreshRate(refreshRate: Float): Boolean

private external fun nativeGetSupportedDisplayRefreshRates(): FloatArray
