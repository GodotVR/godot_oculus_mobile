#include "nativescript_common.h"
#include "ovr_tracking_transform_ns.h"
#include "api/ovr_tracking_transform.h"

static const char *kClassName = "OvrTrackingTransform";

void register_gdnative_tracking_transform(void *p_handle) {
    { // register the constructor and destructor of the OvrTrackingTransform class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_tracking_transform_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_tracking_transform_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrTrackingTransform class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &get_tracking_space;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_tracking_space", attributes, method);

		method.method = &set_tracking_space;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_tracking_space", attributes, method);
	}
}

GDCALLINGCONV void *ovr_tracking_transform_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_tracking_transform_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		api->godot_variant_new_int(&ret, ovrmobile::get_tracking_space(ovr_mobile_session));
	)	
}

GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		int space = api->godot_variant_as_int(p_args[0]); // note that ovrTrackingSpace is an enum in VrApi.h
		api->godot_variant_new_bool(&ret, ovrmobile::set_tracking_space(ovr_mobile_session, space));
	)	
}
