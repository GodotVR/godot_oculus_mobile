/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_performance.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrPerformance

extern "C" {
JNIEXPORT jboolean JNICALL
JNI_METHOD(setClockLevels)(JNIEnv *env, jclass clazz, jint cpu_level, jint gpu_level) {
    return static_cast<jboolean>(ovrmobile::set_clock_levels(get_session(), cpu_level,
                                                             gpu_level));
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(setExtraLatencyMode)(JNIEnv *env, jclass clazz, jint latency_mode) {
    return static_cast<jboolean>(ovrmobile::set_extra_latency_mode(get_session(), latency_mode));
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(setFoveationLevel)(JNIEnv *env, jclass clazz, jint foveation_level) {
    return static_cast<jboolean>(ovrmobile::set_foveation_level(get_session(), foveation_level));
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(setSwapInterval)(JNIEnv *env, jclass clazz, jint swap_interval) {
    return static_cast<jboolean>(ovrmobile::set_swap_interval(get_session(), swap_interval));
}
};