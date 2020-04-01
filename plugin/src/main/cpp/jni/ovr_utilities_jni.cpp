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

namespace {
    inline jfloatArray from_ovrVector3f(JNIEnv *env, ovrVector3f vector) {
        jfloatArray result = env->NewFloatArray(3);
        if (result) {
            float vector_data[3];
            vector_data[0] = vector.x;
            vector_data[1] = vector.y;
            vector_data[2] = vector.z;

            env->SetFloatArrayRegion(result, 0, 3, vector_data);
        }

        return result;
    }
}  // namespace

extern "C" {

JNIEXPORT jfloat JNICALL JNI_METHOD(nativeGetIpd)(JNIEnv *env, jclass clazz) {
    return ovrmobile::get_ipd(get_session());
}

JNIEXPORT jboolean JNICALL
JNI_METHOD(nativeSetDefaultLayerColorScale)(JNIEnv *env, jclass clazz, jfloat red, jfloat green,
                                      jfloat blue, jfloat alpha) {
    return static_cast<jboolean>(ovrmobile::set_default_layer_color_scale(get_session(), red,
                                                                          green, blue, alpha));
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerAngularVelocity)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f angular_velocity = ovrmobile::get_controller_angular_velocity(get_session(),
                                                                              controller_id);
    return from_ovrVector3f(env, angular_velocity);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerLinearVelocity)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f linear_velocity = ovrmobile::get_controller_linear_velocity(get_session(),
                                                                            controller_id);
    return from_ovrVector3f(env, linear_velocity);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerAngularAcceleration)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f angular_acceleration = ovrmobile::get_controller_angular_acceleration(get_session(),
                                                                                      controller_id);
    return from_ovrVector3f(env, angular_acceleration);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerLinearAcceleration)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f linear_acceleration = ovrmobile::get_controller_linear_acceleration(get_session(),
                                                                                    controller_id);
    return from_ovrVector3f(env, linear_acceleration);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetHeadAngularVelocity)(JNIEnv *env, jclass clazz) {
    ovrVector3f angular_velocity = ovrmobile::get_head_angular_velocity(get_session());
    return from_ovrVector3f(env, angular_velocity);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetHeadLinearVelocity)(JNIEnv *env, jclass clazz) {
    ovrVector3f linear_velocity = ovrmobile::get_head_linear_velocity(get_session());
    return from_ovrVector3f(env, linear_velocity);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetHeadAngularAcceleration)(JNIEnv *env, jclass clazz) {
    ovrVector3f angular_acceleration = ovrmobile::get_head_angular_acceleration(get_session());
    return from_ovrVector3f(env, angular_acceleration);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetHeadLinearAcceleration)(JNIEnv *env, jclass clazz) {
    ovrVector3f linear_acceleration = ovrmobile::get_head_linear_acceleration(get_session());
    return from_ovrVector3f(env, linear_acceleration);
}
};