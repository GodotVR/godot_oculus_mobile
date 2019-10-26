/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_utilities.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrUtilities

extern "C" {

JNIEXPORT jfloat JNICALL JNI_METHOD(getIpd)(JNIEnv *env, jclass clazz) {
    return ovrmobile::get_ipd(get_session());
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(setDefaultLayerColorScale)(JNIEnv *env, jclass clazz, jfloat red, jfloat green,
                                      jfloat blue, jfloat alpha) {
    return static_cast<jboolean>(ovrmobile::set_default_layer_color_scale(get_session(), red,
                                                                          green, blue, alpha));
}
};