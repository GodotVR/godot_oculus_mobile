#include "config_common.h"
#include "ovr_utilities.h"

static const char *kClassName = "OvrUtilities";

void register_gdnative_utilities(void *p_handle) {
    { // register the constructor and destructor of the OvrUtilitites class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_utilities_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_utilities_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrUtilities class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &get_ipd;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_ipd", attributes, method);

		method.method = &set_default_layer_color_scale;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_default_layer_color_scale", attributes, method);
	}
}

GDCALLINGCONV void *ovr_utilities_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_utilities_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


GDCALLINGCONV godot_variant get_ipd(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        ovrTracking2 head_tracker = ovr_mobile_session->get_head_tracker();

		// here we compute the vector from the origin of the left eye to the right eye by using the transform part of the view matrix
		float dx = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[0][3] - head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[0][3];
		float dy = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[1][3] - head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[1][3];
		float dz = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[2][3] - head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[2][3];

		// the IPD is then just the length of this vector
        float ipd = sqrtf(dx*dx + dy*dy + dz*dz);
		api->godot_variant_new_real(&ret, ipd);
	)	
}

GDCALLINGCONV godot_variant set_default_layer_color_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		godot_color color = api->godot_variant_as_color(p_args[0]);
		godot_real* pcolor = (godot_real*)&color;
		ovr_mobile_session->set_default_layer_color_scale(pcolor[0], pcolor[1], pcolor[2], pcolor[3]);
		api->godot_variant_new_bool(&ret, true);
	)
}
