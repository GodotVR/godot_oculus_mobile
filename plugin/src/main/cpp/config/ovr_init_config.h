////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module to access and setup the init parameters for the plugin.
// The methods defined in this class must be invoked prior to initializing the Oculus mobile plugin.

#ifndef OVR_INIT_CONFIG_H
#define OVR_INIT_CONFIG_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// Registers the OvrInitConfig class and functions to GDNative.
// This methhod should be called from godot_ovrmobile_nativescript_init.
void register_gdnative_init_config(void *handle);

GDCALLINGCONV void *ovr_init_config_constructor(godot_object *instance, void *method_data);
GDCALLINGCONV void ovr_init_config_destructor(godot_object *instance, void *method_data, void *user_data);

// Set the factor by which to multiply the recommended render target size for the app.
GDCALLINGCONV godot_variant set_render_target_size_multiplier(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

#ifdef __cplusplus
}
#endif

#endif // OVR_INIT_CONFIG_H
