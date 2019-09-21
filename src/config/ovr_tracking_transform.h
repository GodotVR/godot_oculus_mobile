////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that exposes part of the oculus runtime api.
// Each exported class implements one section of the VrApi.h.
// This implements the <Tracking Transform> section.


#ifndef OVR_TRACKING_TRANSFORM_H
#define OVR_TRACKING_TRANSFORM_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrTrackingTransform class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_tracking_transform(void *p_handle);

GDCALLINGCONV void *ovr_tracking_transform_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_tracking_transform_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// implements VrApi.h: ovrTrackingSpace vrapi_GetTrackingSpace( ovrMobile * ovr );
GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrResult vrapi_SetTrackingSpace( ovrMobile * ovr, ovrTrackingSpace whichSpace );
GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrPosef vrapi_LocateTrackingSpace( ovrMobile * ovr, ovrTrackingSpace target );
// not yet implemented


#ifdef __cplusplus
}
#endif

#endif /* !OVR_TRACKING_TRANSFORM */
