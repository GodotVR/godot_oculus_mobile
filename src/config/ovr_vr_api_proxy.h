////////////////////////////////////////////////////////////////////////////////////////////////
// This GDNative module is to be considered temporary and experimental. It exposes part
// of the VrApi.h directly to gdscript and is for low level access of VrApi features.
// It might get replaced by dedicated functions in the future.

#ifndef OVR_VR_API_PROXY_H
#define OVR_VR_API_PROXY_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrVrApiProxy class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_vr_api_proxy(void *p_handle);

GDCALLINGCONV void *ovr_vr_api_proxy_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_vr_api_proxy_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// OVR_VRAPI_EXPORT void vrapi_SetPropertyInt( const ovrJava * java, const ovrProperty propType, const int intVal );
GDCALLINGCONV godot_variant vrapi_set_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// OVR_VRAPI_EXPORT void vrapi_SetPropertyFloat( const ovrJava * java, const ovrProperty propType, const float floatVal );
GDCALLINGCONV godot_variant vrapi_set_property_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// OVR_VRAPI_EXPORT bool vrapi_GetPropertyInt( const ovrJava * java, const ovrProperty propType, int * intVal );
GDCALLINGCONV godot_variant vrapi_get_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


// OVR_VRAPI_EXPORT int vrapi_GetSystemPropertyInt( const ovrJava * java, const ovrSystemProperty propType );
GDCALLINGCONV godot_variant vrapi_get_system_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// OVR_VRAPI_EXPORT float vrapi_GetSystemPropertyFloat( const ovrJava * java, const ovrSystemProperty propType );
GDCALLINGCONV godot_variant vrapi_get_system_property_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// OVR_VRAPI_EXPORT int vrapi_GetSystemPropertyFloatArray( const ovrJava * java, const ovrSystemProperty propType, float * values, int numArrayValues );
// not yet implemented

// OVR_VRAPI_EXPORT int vrapi_GetSystemPropertyInt64Array( const ovrJava * java, const ovrSystemProperty propType, int64_t * values, int numArrayValues );
// not yet implemented

// OVR_VRAPI_EXPORT const char * vrapi_GetSystemPropertyString( const ovrJava * java, const ovrSystemProperty propType );
// not yet implemented


// OVR_VRAPI_EXPORT int vrapi_GetSystemStatusInt( const ovrJava * java, const ovrSystemStatus statusType );
GDCALLINGCONV godot_variant vrapi_get_system_status_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// OVR_VRAPI_EXPORT float vrapi_GetSystemStatusFloat( const ovrJava * java, const ovrSystemStatus statusType );
GDCALLINGCONV godot_variant vrapi_get_system_status_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);



// implements VrApi_Input.h: ovrResult vrapi_GetHandPose(ovrMobile * ovr, const ovrDeviceID deviceID, const double absTimeInSeconds, ovrHandPoseHeader * header);
GDCALLINGCONV godot_variant vrapi_get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif /* !OVR_VRAPIPROXY */
