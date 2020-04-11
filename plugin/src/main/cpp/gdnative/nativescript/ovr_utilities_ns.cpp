#include "api/ovr_utilities.h"
#include "ovr_utilities_ns.h"

static const char *kClassName = "OvrUtilities";

void register_gdnative_utilities(void *p_handle) {
    { // register the constructor and destructor of the OvrUtilitites class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_utilities_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_utilities_destructor;

		godot::nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrUtilities class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &get_ipd;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_ipd", attributes, method);

		method.method = &set_default_layer_color_scale;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_default_layer_color_scale", attributes, method);

		method.method = &get_controller_angular_velocity;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_controller_angular_velocity", attributes, method);
		method.method = &get_controller_linear_velocity;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_controller_linear_velocity", attributes, method);
		method.method = &get_controller_angular_acceleration;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_controller_angular_acceleration", attributes, method);
		method.method = &get_controller_linear_acceleration;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_controller_linear_acceleration", attributes, method);

		method.method = &get_head_angular_velocity;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_head_angular_velocity", attributes, method);
		method.method = &get_head_linear_velocity;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_head_linear_velocity", attributes, method);
		method.method = &get_head_angular_acceleration;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_head_angular_acceleration", attributes, method);
		method.method = &get_head_linear_acceleration;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_head_linear_acceleration", attributes, method);

	}
}

GDCALLINGCONV void *ovr_utilities_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)godot::api->godot_alloc(sizeof(ovr_config_data_struct));
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
	CHECK_USER_DATA(
		godot::api->godot_variant_new_real(&ret, ovrmobile::get_ipd(ovr_mobile_session));
	)
}

GDCALLINGCONV godot_variant set_default_layer_color_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		godot_color color = godot::api->godot_variant_as_color(p_args[0]);
		godot_real* pcolor = (godot_real*)&color;
		godot::api->godot_variant_new_bool(&ret, ovrmobile::set_default_layer_color_scale(ovr_mobile_session, pcolor[0], pcolor[1], pcolor[2], pcolor[3]));
	)
}


GDCALLINGCONV godot_variant get_controller_angular_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		int controller_id = godot::api->godot_variant_as_int(p_args[0]);
		ovrVector3f angular_velocity = ovrmobile::get_controller_angular_velocity(ovr_mobile_session, controller_id);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, angular_velocity);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_controller_linear_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		int controller_id = godot::api->godot_variant_as_int(p_args[0]);
		ovrVector3f linear_velocity = ovrmobile::get_controller_linear_velocity(ovr_mobile_session, controller_id);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, linear_velocity);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_controller_angular_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		int controller_id = godot::api->godot_variant_as_int(p_args[0]);
		ovrVector3f angular_acceleration = ovrmobile::get_controller_angular_acceleration(ovr_mobile_session, controller_id);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, angular_acceleration);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_controller_linear_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		int controller_id = godot::api->godot_variant_as_int(p_args[0]);
		ovrVector3f linear_acceleration = ovrmobile::get_controller_linear_acceleration(ovr_mobile_session, controller_id);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, linear_acceleration);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}


GDCALLINGCONV godot_variant get_head_angular_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		ovrVector3f v = ovrmobile::get_head_angular_velocity(ovr_mobile_session);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, v);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_head_angular_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		ovrVector3f v = ovrmobile::get_head_angular_acceleration(ovr_mobile_session);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, v);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_head_linear_velocity(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		ovrVector3f v = ovrmobile::get_head_linear_velocity(ovr_mobile_session);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, v);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}

GDCALLINGCONV godot_variant get_head_linear_acceleration(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		ovrVector3f v = ovrmobile::get_head_linear_acceleration(ovr_mobile_session);
		godot_vector3 gd_vector;
		ovrmobile::godot_vector3_from_ovrVector3f(&gd_vector, v);
		godot::api->godot_variant_new_vector3(&ret, &gd_vector);
	)
}
