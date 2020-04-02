/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "ovr_mobile_session.h"
#include "jni_common.h"
#include "ovr_mobile_plugin_wrapper.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrMobilePlugin

extern "C" {
JNIEXPORT void JNICALL JNI_METHOD(initializeWrapper)(JNIEnv* env,
                                                     jobject object) {
  ovrmobile::OvrMobilePluginWrapper::initializeWrapper(env, object);
}

JNIEXPORT void JNICALL JNI_METHOD(uninitializeWrapper)(JNIEnv* env,
                                                       jobject object) {
  ovrmobile::OvrMobilePluginWrapper::uninitializeWrapper(env);
}
};