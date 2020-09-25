/**
 * Created by Fredia Huya-Kouadio.
 */

#include "api/ovr_display.h"
#include "jni_common.h"
#include <jni.h>

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrDisplay

extern "C" {

JNIEXPORT jboolean JNICALL JNI_METHOD(nativeSetColorSpace)(JNIEnv *env,
                                                           jclass,
                                                           jint color_space) {
    return ovrmobile::set_color_space(get_session(), static_cast<ovrColorSpace>(color_space));
}

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetColorSpace)(JNIEnv *env, jclass) {
    return ovrmobile::get_color_space(get_session());
}

JNIEXPORT jboolean JNICALL JNI_METHOD(nativeSetDisplayRefreshRate)(JNIEnv *env,
                                                                   jclass clazz,
                                                                   jfloat refresh_rate) {
    return static_cast<jboolean>(ovrmobile::set_display_refresh_rate(get_session(), refresh_rate));
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetSupportedDisplayRefreshRates)(JNIEnv *env,
                                                                                jclass clazz) {
    std::vector<float> refresh_rates =
            ovrmobile::get_supported_display_refresh_rates(get_session());

    unsigned long count = refresh_rates.size();
    jfloatArray result = env->NewFloatArray(count);
    env->SetFloatArrayRegion(result, 0, count, refresh_rates.data());

    return result;
}
};
