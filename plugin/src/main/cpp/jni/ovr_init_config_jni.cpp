/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "api/ovr_init_config.h"
#include "jni_common.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrInitConfig

extern "C" {

JNIEXPORT jboolean JNICALL
JNI_METHOD(setRenderTargetSizeMultiplier)(JNIEnv *env, jclass clazz, jdouble multiplier) {
    return static_cast<jboolean>(ovrmobile::set_render_target_size_multiplier(get_session(),
                                                                              multiplier));
}

};
