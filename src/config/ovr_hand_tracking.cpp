#include "config_common.h"
#include "ovr_hand_tracking.h"

static const char *kClassName = "OvrHandTracking";

void register_gdnative_hand_tracking(void *p_handle) {
    { // register the constructor and destructor of the OvrHandTracking class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_hand_tracking_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_hand_tracking_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrHandTracking class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &get_hand_pose;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_hand_pose", attributes, method);

		method.method = &get_hand_scale;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_hand_scale", attributes, method);
		
	}
}

GDCALLINGCONV void *ovr_hand_tracking_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_hand_tracking_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


GDCALLINGCONV godot_variant get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        api->godot_variant_new_real(&ret, 0.0); // in case sth. fails below we return 0.0 to always have a float return value
		int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
		const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
		if (pController != nullptr) {
			const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
			if (pState != nullptr && pState->connected) {
				godot_array rotations = api->godot_variant_as_array(p_args[1]);

				if (api->godot_array_size(&rotations) != ovrHandBone_Max) {
					ALOGE("get_hand_pose(...) expect p_args[1] to be an array of size %d; got %d.", ovrHandBone_Max, api->godot_array_size(&rotations));
				} else {

					for (int i = 0; i < ovrHandBone_Max; i++) {
						//godot_quat quat = godot_variant_as_quat(godot_array_get(rotations, i));
						godot_variant v_quat;
						godot_quat g_quat;
						//ovrQuatf ovr_quat = pose.BoneRotations[i];
						ovrQuatf ovr_quat = pState->hand_pose.BoneRotations[i];
						api->godot_quat_new(&g_quat, ovr_quat.x, ovr_quat.y, ovr_quat.z, ovr_quat.w);
						api->godot_variant_new_quat(&v_quat, &g_quat);
						api->godot_array_set(&rotations, i, &v_quat);
					}

					// we return a confidence value how well the hand is tracked. If the ovr sdk return untracked it is 0.0
					// low confidence is 0.5 and full confidence is 1.0
					float return_value = 0.0f;

					if (pState->hand_pose.Status == ovrHandTrackingStatus_Tracked) {
						if (pState->hand_pose.HandConfidence == ovrConfidence_HIGH) {
							return_value = 1.0f;
						} else { // in sdk 1.29 there are only HIGH and LOW as confidence values if the hand is tracked
							return_value = 0.5f;
						}
					}

					api->godot_variant_new_real(&ret, return_value);
				}
			}
		}
	)
}


GDCALLINGCONV godot_variant get_hand_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        api->godot_variant_new_real(&ret, 0.0); // in case sth. fails below we return 0.0 to always have a float return value
		int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
		const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
		if (pController != nullptr) {
			const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
			if (pState != nullptr && pState->connected) {
                api->godot_variant_new_real(&ret, pState->hand_pose.HandScale);
            }
        }
    )
}