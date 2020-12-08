/**
 * Created by Fredia Huya-Kouadio.
 */

#include "api/ovr_utilities.h"
#include "jni_common.h"
#include <jni.h>

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrUtilities

extern "C" {

JNIEXPORT jfloat JNICALL JNI_METHOD(nativeGetIpd)(JNIEnv *env, jclass clazz) {
    return ovrmobile::get_ipd(get_session());
}

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetRenderTargetWidth)(JNIEnv *env, jclass) {
    return get_session()->get_render_target_width();
}

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetRenderTargetHeight)(JNIEnv *env, jclass) {
    return get_session()->get_render_target_height();
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetEyeFov)(JNIEnv *env, jclass, jint eye) {
    ovrVector4f eye_fov = get_session()->get_eye_fov(static_cast<ovrEye>(eye));
    return from_ovrVector4f(env, eye_fov);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetEyeViewportBounds)(JNIEnv *env,
                                                                     jclass,
                                                                     jint eye) {
    ovrVector4f eye_viewport_bounds =
            get_session()->get_eye_viewport_bound(static_cast<ovrEye>(eye));
    return from_ovrVector4f(env, eye_viewport_bounds);
}

JNIEXPORT jboolean JNICALL JNI_METHOD(nativeSetDefaultLayerColorScale)(JNIEnv *env,
                                                                       jclass clazz,
                                                                       jfloat red,
                                                                       jfloat green,
                                                                       jfloat blue,
                                                                       jfloat alpha) {
    return static_cast<jboolean>(
            ovrmobile::set_default_layer_color_scale(get_session(), red, green, blue, alpha));
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetControllerAngularVelocity)(JNIEnv *env,
                                                                             jclass clazz,
                                                                             jint controller_id) {
    ovrVector3f angular_velocity =
            ovrmobile::get_controller_angular_velocity(get_session(), controller_id);
    return from_ovrVector3f(env, angular_velocity);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetControllerLinearVelocity)(JNIEnv *env,
                                                                            jclass clazz,
                                                                            jint controller_id) {
    ovrVector3f linear_velocity =
            ovrmobile::get_controller_linear_velocity(get_session(), controller_id);
    return from_ovrVector3f(env, linear_velocity);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerAngularAcceleration)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f angular_acceleration =
            ovrmobile::get_controller_angular_acceleration(get_session(), controller_id);
    return from_ovrVector3f(env, angular_acceleration);
}

JNIEXPORT jfloatArray JNICALL
JNI_METHOD(nativeGetControllerLinearAcceleration)(JNIEnv *env, jclass clazz, jint controller_id) {
    ovrVector3f linear_acceleration =
            ovrmobile::get_controller_linear_acceleration(get_session(), controller_id);
    return from_ovrVector3f(env, linear_acceleration);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetHeadAngularVelocity)(JNIEnv *env, jclass clazz) {
    ovrVector3f angular_velocity = ovrmobile::get_head_angular_velocity(get_session());
    return from_ovrVector3f(env, angular_velocity);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetHeadLinearVelocity)(JNIEnv *env, jclass clazz) {
    ovrVector3f linear_velocity = ovrmobile::get_head_linear_velocity(get_session());
    return from_ovrVector3f(env, linear_velocity);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetHeadAngularAcceleration)(JNIEnv *env,
                                                                           jclass clazz) {
    ovrVector3f angular_acceleration = ovrmobile::get_head_angular_acceleration(get_session());
    return from_ovrVector3f(env, angular_acceleration);
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetHeadLinearAcceleration)(JNIEnv *env,
                                                                          jclass clazz) {
    ovrVector3f linear_acceleration = ovrmobile::get_head_linear_acceleration(get_session());
    return from_ovrVector3f(env, linear_acceleration);
}
};
