/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_display_refresh_rate.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrDisplayRefreshRate

extern "C" {
JNIEXPORT jboolean JNICALL
JNI_METHOD(setDisplayRefreshRate)(JNIEnv *env, jclass clazz, jfloat refresh_rate) {
    return static_cast<jboolean>(ovrmobile::set_display_refresh_rate(get_session(),
                                                                     refresh_rate));
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(getSupportedDisplayRefreshRates)(JNIEnv *env, jclass clazz) {
    std::vector<float> refresh_rates = ovrmobile::get_supported_display_refresh_rates(
            get_session());

    unsigned long count = refresh_rates.size();
    jfloatArray result = env->NewFloatArray(count);
    env->SetFloatArrayRegion(result, 0, count, refresh_rates.data());

    return result;
}
};