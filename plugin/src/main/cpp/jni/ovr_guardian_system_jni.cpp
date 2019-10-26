/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_guardian_system.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrGuardianSystem

extern "C" {
    JNIEXPORT jboolean JNICALL JNI_METHOD(isBoundaryVisible)(JNIEnv *env, jclass clazz) {
        return static_cast<jboolean>(ovrmobile::get_boundary_visible(get_session()));
    }

    JNIEXPORT jboolean JNICALL JNI_METHOD(requestBoundaryVisible)(JNIEnv *env, jclass clazz, jboolean visible) {
        return static_cast<jboolean>(ovrmobile::request_boundary_visible(get_session(), visible));
    }
};