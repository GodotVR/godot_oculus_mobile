////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that exposes part of the oculus api.
// Each exported class implements one section of the VrApi.h.
// This implements the <Guardian System> section.

#ifndef OVR_GUARDIAN_SYSTEM_NS_H
#define OVR_GUARDIAN_SYSTEM_NS_H

#include "nativescript_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrGuardianSystem class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_guardian_system(void *p_handle);

GDCALLINGCONV void *ovr_guardian_system_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_guardian_system_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// implements VrApi.h: ovrResult vrapi_GetBoundaryGeometry( ovrMobile * ovr, const uint32_t pointsCountInput, uint32_t * pointsCountOutput, ovrVector3f * points );
GDCALLINGCONV godot_variant get_boundary_geometry(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

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



#ifdef __cplusplus
}
#endif

#endif /* !OVR_GUARDIAN_SYSTEM_NS_H */
