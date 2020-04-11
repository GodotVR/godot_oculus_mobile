////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that wraps some utility functions that need the VrApi

#ifndef OVR_UTILITIES_NS_H
#define OVR_UTILITIES_NS_H

#include "nativescript_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrUtilities class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_utilities(void *p_handle);

GDCALLINGCONV void *ovr_utilities_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_utilities_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// uses the internal left and right view matrix to compute the IPD. Returns a float in GDScript
GDCALLINGCONV godot_variant get_ipd(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// Expects a Color parameter in GDScript and sets the color multiplier for the default layer used by the VrAPI compositor
GDCALLINGCONV godot_variant set_default_layer_color_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant get_controller_angular_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_controller_linear_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_controller_angular_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_controller_linear_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant get_head_angular_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_head_linear_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_head_angular_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_head_linear_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif /* !OVR_UTILITIES_NS_H */
