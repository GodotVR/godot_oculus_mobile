////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that exposes part of the oculus runtime api.
// Each exported class implements one section of the VrApi.h.
// This implements the <Performance> section.


#ifndef OVR_PERFORMANCE_NS_H
#define OVR_PERFORMANCE_NS_H

#include "gdnative/godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// Registers the OvrPerformance class and functions to GDNative.
// This method should be called from godot_ovrmobile_nativescript_init.
void register_gdnative_performance(void *handle);

GDCALLINGCONV void *ovr_performance_constructor(godot_object *instance, void *method_data);
GDCALLINGCONV void ovr_performance_destructor(godot_object *instance, void *method_data,
                                              void *user_data);

// implements VrApi.h: ovrResult vrapi_SetClockLevels( ovrMobile * ovr, const int32_t cpuLevel, const int32_t gpuLevel );
GDCALLINGCONV godot_variant set_clock_levels(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h ovrResult vrapi_SetExtraLatencyMode( ovrMobile * ovr, const ovrExtraLatencyMode mode );
// Valid int values for the latency mode are defined by ovrExtraLatencyMode enum in VrApi_Types.h
GDCALLINGCONV godot_variant set_extra_latency_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// Set the fixed foveated rendering level if it's available.
// Returns true if it's available and the given level is valid, false otherwise.
// For additional information, check the following docs:
// - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
// - Oculus Go: https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/
GDCALLINGCONV godot_variant set_foveation_level(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// Enables or disables dynamic foveation
// Returns true if it's available 
GDCALLINGCONV godot_variant set_enable_dynamic_foveation(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


// Sets the swap interval to control the application frame timing.
// See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing for additional background.
GDCALLINGCONV godot_variant set_swap_interval(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif // OVR_PERFORMANCE_NS_H
