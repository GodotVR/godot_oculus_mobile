////////////////////////////////////////////////////////////////////////////////////////////////
// This GDNative module is to be considered temporary and experimental. It exposes part
// of the VrApi.h directly to gdscript and is for low level access of VrApi features.
// It might get replaced by dedicated functions in the future.

#ifndef OVR_HAND_TRACKING_NS_H
#define OVR_HAND_TRACKING_NS_H

#include "gdnative/godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrVrApiProxy class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_hand_tracking(void *p_handle);

GDCALLINGCONV void *ovr_hand_tracking_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_hand_tracking_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// get_hand_pose(controller_id : int, pose : Array[24]);
// fills the tracked pose in the given array as quaternions for the given controller id; returns a confidence value in [0.0, 1.0] based
// on the hand tracking confidence returned by VrApi. If the controller is not connected or VR not initialized it returns nil.
GDCALLINGCONV godot_variant get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// get_hand_scale(controller_id : int);
// returns 0.0 if the system is unable to get the hand scale; else returns the scale given by VrApi
GDCALLINGCONV godot_variant get_hand_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// check if the current pointer pose is valid; only then get_pointer_pose will return a useful value
GDCALLINGCONV godot_variant is_pointer_pose_valid(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// return the VrApi hand pointer pose
GDCALLINGCONV godot_variant get_pointer_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


#ifdef __cplusplus
}
#endif

#endif /* !OVR_HAND_TRACKING_NS_H */
