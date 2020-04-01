#include "nativescript_common.h"
#include "ovr_vr_api_proxy_ns.h"

static const char *kClassName = "OvrVrApiProxy";

void register_gdnative_vr_api_proxy(void *p_handle) {
    { // register the constructor and destructor of the OvrVrApiProxy class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_vr_api_proxy_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_vr_api_proxy_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrVrApiProxy class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &vrapi_set_property_int;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_set_property_int", attributes, method);
		method.method = &vrapi_set_property_float;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_set_property_float", attributes, method);
		method.method = &vrapi_get_property_int;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_property_int", attributes, method);
		
		method.method = &vrapi_get_system_property_int;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_system_property_int", attributes, method);
		method.method = &vrapi_get_system_property_float;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_system_property_float", attributes, method);
		
		method.method = &vrapi_get_system_status_int;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_system_status_int", attributes, method);
		method.method = &vrapi_get_system_status_float;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_system_status_float", attributes, method);

		method.method = &vrapi_get_hand_pose;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "vrapi_get_hand_pose", attributes, method);

		
	}
}

GDCALLINGCONV void *ovr_vr_api_proxy_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_vr_api_proxy_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


GDCALLINGCONV godot_variant vrapi_set_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrProperty propType = (ovrProperty)api->godot_variant_as_int(p_args[0]);
	    int propValue = api->godot_variant_as_int(p_args[1]);
	    vrapi_SetPropertyInt(ovr_java, propType, propValue);
	    api->godot_variant_new_bool(&ret, true); // there seams to be no error handling for the VrApi SetProperty function so we just return true here
	)
}

GDCALLINGCONV godot_variant vrapi_set_property_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrProperty propType = (ovrProperty)api->godot_variant_as_int(p_args[0]);
	    godot_real propValue = api->godot_variant_as_real(p_args[1]);
	    vrapi_SetPropertyFloat(ovr_java, propType, propValue);
	    api->godot_variant_new_bool(&ret, true); // there seams to be no error handling for the VrApi SetProperty function so we just return true here
	)
}

GDCALLINGCONV godot_variant vrapi_get_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrProperty propType = (ovrProperty)api->godot_variant_as_int(p_args[0]);
		int prop = 0;
		bool valid = vrapi_GetPropertyInt(ovr_java, propType, &prop);
		if (valid) {
			api->godot_variant_new_int(&ret, prop);
		} else {
			api->godot_variant_new_nil(&ret); // return nil when the query was invalid
		}
	)
}



GDCALLINGCONV godot_variant vrapi_get_system_property_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrSystemProperty propType = (ovrSystemProperty)api->godot_variant_as_int(p_args[0]);
		int prop = vrapi_GetSystemPropertyInt(ovr_java, propType);
		api->godot_variant_new_int(&ret, prop);
	)
}

GDCALLINGCONV godot_variant vrapi_get_system_property_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrSystemProperty propType = (ovrSystemProperty)api->godot_variant_as_int(p_args[0]);
		godot_real prop = vrapi_GetSystemPropertyFloat(ovr_java, propType);
		api->godot_variant_new_real(&ret, prop);
	)
}


GDCALLINGCONV godot_variant vrapi_get_system_status_int(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrSystemStatus statusType = (ovrSystemStatus)api->godot_variant_as_int(p_args[0]);
		int status = vrapi_GetSystemStatusInt(ovr_java, statusType);
		api->godot_variant_new_int(&ret, status);
	)
}

GDCALLINGCONV godot_variant vrapi_get_system_status_float(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrSystemStatus statusType = (ovrSystemStatus)api->godot_variant_as_int(p_args[0]);
		godot_real status = vrapi_GetSystemStatusFloat(ovr_java, statusType);
		api->godot_variant_new_real(&ret, status);
	)
}



GDCALLINGCONV godot_variant vrapi_get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		int controller_id = api->godot_variant_as_int(p_args[0]);
		const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
		if (pController != nullptr) {
			const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state_by_id(controller_id);
			if (pState != nullptr && pState->connected) {
				//ovrHandPose pose;
				//pose.Header.Version = ovrHandVersion_1;
				//vrapi_GetHandPose(ovr, pState->header.DeviceID, ovr_mobile_session->get_predicted_display_time(), &pose.Header);
				
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

					api->godot_variant_new_bool(&ret, true);
				}
			}
		}
	)
}
