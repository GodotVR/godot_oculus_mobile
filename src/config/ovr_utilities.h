////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that wraps some utility functions that need the VrApi

#ifndef OVR_UTILITIES_H
#define OVR_UTILITIES_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

void register_gdnative_utilities(void *p_handle);

GDCALLINGCONV void *ovr_utilities_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_utilities_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

GDCALLINGCONV godot_variant get_ipd(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant set_default_layer_color_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif /* !OVR_UTILITIES */
