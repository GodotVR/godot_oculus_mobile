/**
* Created by Fredia Huya-Kouadio. 
*/

#include "ovr_mobile_plugin_wrapper.h"
#include "common.h"

namespace ovrmobile {

jobject OvrMobilePluginWrapper::ovr_mobile_plugin_instance = nullptr;
jmethodID OvrMobilePluginWrapper::on_headset_mounted_id = nullptr;
jmethodID OvrMobilePluginWrapper::on_headset_unmounted_id = nullptr;

OvrMobilePluginWrapper::OvrMobilePluginWrapper() {}

OvrMobilePluginWrapper::~OvrMobilePluginWrapper() {}

void OvrMobilePluginWrapper::initializeWrapper(JNIEnv* env,
                                               jobject ovr_mobile_plugin) {
  ovr_mobile_plugin_instance = env->NewGlobalRef(ovr_mobile_plugin);
  ALOG_ASSERT(ovr_mobile_plugin_instance != nullptr, "Invalid jobject value.");

  jclass
      ovr_mobile_plugin_class = env->GetObjectClass(ovr_mobile_plugin_instance);
  ALOG_ASSERT(ovr_mobile_plugin_class != nullptr, "Invalid jclass value.");

  on_headset_mounted_id =
      env->GetMethodID(ovr_mobile_plugin_class, "onHeadsetMounted", "()V");
  ALOG_ASSERT(on_headset_mounted_id != nullptr,
              "Unable to find onHeadsetMounted");

  on_headset_unmounted_id =
      env->GetMethodID(ovr_mobile_plugin_class, "onHeadsetUnmounted", "()V");
  ALOG_ASSERT(on_headset_unmounted_id != nullptr,
              "Unable to find onHeadsetUnmounted");
}

void OvrMobilePluginWrapper::uninitializeWrapper(JNIEnv* env) {
  if (ovr_mobile_plugin_instance) {
    env->DeleteGlobalRef(ovr_mobile_plugin_instance);
    ovr_mobile_plugin_instance = nullptr;
    on_headset_mounted_id = nullptr;
    on_headset_unmounted_id = nullptr;
  }
}

void OvrMobilePluginWrapper::on_headset_mounted() {
  if (ovr_mobile_plugin_instance && on_headset_mounted_id) {
    JNIEnv *env = android_api->godot_android_get_env();
    env->CallVoidMethod(ovr_mobile_plugin_instance, on_headset_mounted_id);
  }
}

void OvrMobilePluginWrapper::on_headset_unmounted() {
  if (ovr_mobile_plugin_instance && on_headset_unmounted_id) {
    JNIEnv* env = android_api->godot_android_get_env();
    env->CallVoidMethod(ovr_mobile_plugin_instance, on_headset_unmounted_id);
  }
}
} // namespace ovrmobile