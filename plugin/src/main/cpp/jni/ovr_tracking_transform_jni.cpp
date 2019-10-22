/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_tracking_transform.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrTrackingTransform

extern "C" {

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetTrackingSpace)(JNIEnv *env, jclass clazz) {
    return ovrmobile::get_tracking_space(get_session());
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(nativeSetTrackingSpace)(JNIEnv *env, jclass clazz, jint tracking_space) {
    return static_cast<jboolean>(ovrmobile::set_tracking_space(get_session(), tracking_space));
}
};
