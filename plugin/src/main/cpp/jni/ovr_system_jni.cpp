/**
 * Created by Fredia Huya-Kouadio.
 */

#include "api/ovr_system.h"
#include "jni_common.h"
#include <jni.h>

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrSystem

extern "C" {

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetDeviceType)(JNIEnv *, jclass) {
    return ovrmobile::get_device_type(get_session());
}

JNIEXPORT jstring JNICALL JNI_METHOD(nativeGetDriverVersion)(JNIEnv *env, jclass) {
    return string_to_jstring(env, ovrmobile::get_driver_version());
}
};
