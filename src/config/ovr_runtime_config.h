////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module to access and setup the runtime parameters for the plugin.
// The methods defined here must be invoked after the Oculus mobile plugin has been initialized.


#ifndef OVR_RUNTIME_CONFIG_H
#define OVR_RUNTIME_CONFIG_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// Registers the OvrRuntimeConfig class and functions to GDNative.
// This method should be called from godot_ovrmobile_nativescript_init.
void register_gdnative_runtime_config(void *handle);

GDCALLINGCONV void *ovr_runtime_config_constructor(godot_object *instance, void *method_data);
GDCALLINGCONV void ovr_runtime_config_destructor(godot_object *instance, void *method_data, void*user_data);

//-----------------------------------------------------------------
// Display Refresh Rate
//-----------------------------------------------------------------

// implements VrApi.h: ovrResult vrapi_SetDisplayRefreshRate(ovrMobile * ovr, const float refreshRate);
GDCALLINGCONV godot_variant set_display_refresh_rate(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

// Utility method to access the display refresh rates supported by the device.
GDCALLINGCONV godot_variant get_supported_display_refresh_rates(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

//-----------------------------------------------------------------
// Guardian System
//
//-----------------------------------------------------------------

// implements VrApi.h: ovrResult vrapi_GetBoundaryGeometry( ovrMobile * ovr, const uint32_t pointsCountInput, uint32_t * pointsCountOutput, ovrVector3f * points );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryOrientedBoundingBox( ovrMobile * ovr, ovrPosef * pose, ovrVector3f * scale );
GDCALLINGCONV godot_variant get_boundary_oriented_bounding_box(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrResult vrapi_TestPointIsInBoundary( ovrMobile * ovr, const ovrVector3f point, bool * pointInsideBoundary, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryTriggerState( ovrMobile * ovr, const ovrTrackedDeviceTypeId deviceId, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_RequestBoundaryVisible( ovrMobile * ovr, const bool visible );
GDCALLINGCONV godot_variant request_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

//ovrResult vrapi_GetBoundaryVisible( ovrMobile * ovr, bool * visible );
GDCALLINGCONV godot_variant get_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

//-----------------------------------------------------------------
// Tracking Transform
//
//-----------------------------------------------------------------

// implements VrApi.h: ovrTrackingSpace vrapi_GetTrackingSpace( ovrMobile * ovr );
GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrResult vrapi_SetTrackingSpace( ovrMobile * ovr, ovrTrackingSpace whichSpace );
GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrPosef vrapi_LocateTrackingSpace( ovrMobile * ovr, ovrTrackingSpace target );
// not yet implemented

//-----------------------------------------------------------------
// Performance
//-----------------------------------------------------------------

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

// Sets the swap interval to control the application frame timing.
// See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing for additional background.
GDCALLINGCONV godot_variant set_swap_interval(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif // OVR_RUNTIME_CONFIG_H
