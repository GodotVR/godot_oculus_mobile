#ifndef OVR_INPUT_NS_H
#define OVR_INPUT_NS_H

#include "nativescript_common.h"

#ifdef __cplusplus
extern "C" {
#endif

  // Registers the OvrInput class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
  void register_gdnative_input(void *handle);

  GDCALLINGCONV void *ovr_input_constructor(godot_object *instance, void *method_data);
  GDCALLINGCONV void ovr_input_destructor(godot_object *instance, void *method_data, void *user_data);

  GDCALLINGCONV godot_variant vibrate_controller(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args);

#ifdef __cplusplus
};
#endif

#endif // OVR_INPUT_NS_H
